#ifndef MessageQ_hpp_
#define MessageQ_hpp_

#include <string>

#include "Queue.hpp"

namespace Volatus {

class Message {
 public:
  Message() =default;
  virtual ~Message() =default;
  
  virtual std::string_view id() = 0;
};

class MessageQ : public Queue<Message> {
 public:
  MessageQ(int maxSize) : Queue{maxSize} {}
  ~MessageQ();

  /**
   * Sends a message packed with a Promise so that a response can be returned
   * and the caller of this function is blocked until that response occurs or
   * the request times out.
   */
  template <typename T>
  std::optional<T> request(std::unique_ptr<Message> m,
                           Timeout_ms timeout = -1ms);

 private:
};

template <typename T>
std::optional<T> MessageQ::request(std::unique_ptr<Message> m,
                                   Timeout_ms timeout) {
  return {};
}

}  // namespace Volatus

#endif  // MessageQ_hpp_
