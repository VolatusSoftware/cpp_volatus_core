#ifndef Queue_hpp_
#define Queue_hpp_

#include <chrono>
#include <condition_variable>
#include <deque>
#include <mutex>

namespace Volatus {

using namespace std::literals::chrono_literals;

using Timeout = std::chrono::nanoseconds;

template <typename T>
class Queue {
 public:
  Queue(int maxSize = -1);
  ~Queue() =default;

  bool enqueue(std::unique_ptr<T> element, Timeout_ms timeout = -1ms);
  bool enqueueFront(std::unique_ptr<T> element, Timeout_ms timeout = -1ms);
  std::unique_ptr<T> lossyEnqueue(std::unique_ptr<T> element, Timeout_ms timeout = 0ms);

  std::unique_ptr<T> dequeue(Timeout_ms timeout = -1ms);

  bool isEmpty();
  bool isFull();

  std::size_t size();

 private:
  int m_maxSize = -1;
  std::mutex m_mutex{};
  std::condition_variable m_added{};
  std::condition_variable m_removed{};
  std::deque<std::unique_ptr<T>> m_deque{};
};

template <typename T>
Queue<T>::Queue(int maxSize): m_maxSize{maxSize} {
    if (m_maxSize == 0 || m_maxSize < -1) {
        throw std::runtime_error("Max size must be greater than 0 or be -1");
    }
}

template <typename T>
bool Queue<T>::isEmpty() {
    std::unique_lock<std::mutex> lock{m_mutex};
    return m_deque.empty();
}

template <typename T>
bool Queue<T>::isFull() {
    std::unique_lock<std::mutex> lock{m_mutex};
    return m_deque.size() == m_maxSize;
}

template <typename T>
std::size_t Queue<T>::size() {
    std::unique_lock<std::mutex> lock{m_mutex};
    return m_deque.size();
}

template <typename T>
bool Queue<T>::enqueue(std::unique_ptr<T> element, Timeout_ms timeout) {
    std::unique_lock<std::mutex> lock{m_mutex};
    if (m_deque.size() == m_maxSize) {
        auto status = m_removed.wait_for(lock, timeout);
        if (status == std::cv_status::timeout) {
            return false;
        }
    }

    m_deque.push_back(std::move(element));
    lock.unlock();
    m_added.notify_one();

    return true;
}

template <typename T>
bool Queue<T>::enqueueFront(std::unique_ptr<T> element, Timeout_ms timeout) {
    std::unique_lock<std::mutex> lock{m_mutex};
    if (m_deque.size() == m_maxSize) {
        auto status = m_removed.wait_for(lock, timeout);
        if (status == std::cv_status::timeout) {
            return false;
        }
    }

    m_deque.push_front(std::move(element));
    lock.unlock();
    m_added.notify_one();

    return true;
}

template <typename T>
std::unique_ptr<T> Queue<T>::lossyEnqueue(std::unique_ptr<T> element, Timeout_ms timeout) {
    std::unique_ptr<T> removed{};

    std::unique_lock<std::mutex> lock{m_mutex};
    if (m_deque.size() == m_maxSize) {
        if (timeout > 0ms) {
            auto status = m_removed.wait_for(lock, timeout);
            if (status == std::cv_status::timeout) {
                lock.lock();
            }
        }

        if (m_deque.size() == m_maxSize) {
            removed = std::move(m_deque.front());
            m_deque.pop_front();
        }
    }

    m_deque.push_back(std::move(element));
    lock.unlock();
    m_added.notify_one();

    return removed;
}

template <typename T>
std::unique_ptr<T> Queue<T>::dequeue(Timeout_ms timeout) {
    std::unique_lock<std::mutex> lock{m_mutex};
    if (m_deque.empty()) {
        auto status = m_added.wait_for(lock, timeout);
        if (status == std::cv_status::timeout) {
            return {};
        }
    }

    auto element = std::move(m_deque.front());
    m_deque.pop_front();
    m_removed.notify_one();

    return element;
}

}  // namespace Volatus

#endif  // Queue_hpp_
