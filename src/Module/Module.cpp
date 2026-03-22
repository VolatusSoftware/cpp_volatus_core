#include "Module/Module.hpp"

#include <thread>

namespace Volatus {

using namespace std::string_view_literals;

Module::Module() : m_selfQ{std::make_shared<MessageQ>(qSize())} {}

Module::~Module() {}

std::weak_ptr<MessageQ> Module::launchAsRoot(ConfigElement* config) {
  m_config = config;

  launch();

  return m_selfQ;
}

std::weak_ptr<MessageQ> Module::launchAsNested(std::weak_ptr<MessageQ> parentQ,
                                               ConfigElement* config) {
  m_config = config;
  m_parentQ = parentQ.lock();

  launch();

  return m_selfQ;
}

ConfigElement* Module::getConfig() { return m_config; }

TaskConfig* Module::getTaskConfig() {
  return dynamic_cast<TaskConfig*>(m_config);
}

std::unique_ptr<Message> Module::nextMessage(Timeout timeout) {
  auto start = std::chrono::steady_clock::now();

  auto remaining = timeout;
  bool read = true;

  //Not checking remaining > 0ns since we always want to attempt to read once
  while (read) {
    auto m = m_selfQ->dequeue(remaining);
    if (m) {
      auto id = m->id();

      // Check for internal messages, starts with "<"
      // Return a new instance of the appropriate message and let the incoming message go out of scope.
      if (id.starts_with("<")) {
        if (id == "<CLOSE>") {
          //
          m_closing = true;
          return std::make_unique<CloseMessage>();
        }
        if (id == "<STOP>") {
          return std::make_unique<StopMessage>();
        }
        if (id == "<LASTACK>") {
          return std::make_unique<LastAckMessage>();
        }



        if (remaining < 0ns) {
          remaining = timeout - (start - std::chrono::steady_clock::now());
          read = remaining > 0ns;

          //clamp to 0 when using timeout
          if (remaining < 0ns) {
            remaining = 0ns;
          }
        }
      }

      // not an internal message, return external message
      return m;
    }

    // timed out, no message
    return nullptr;
  }
}

void Module::registerNested(std::unique_ptr<Module> module) {
  m_nested.push_back(std::move(module));
}

}  // namespace Volatus
