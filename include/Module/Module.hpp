#ifndef Module_hpp_
#define Module_hpp_

#include "MessageQ.hpp"
#include "VolatusConfig/TaskConfig.hpp"

namespace Volatus {

  enum class ModuleState {
    UNKNOWN,
    Launched,
    Starting,
    Running,
    Stopping,
    Stopped,

    ErrorStarting,
    ErrorRunning,
    ErrorStopping
  };

struct NestedInfo {
  std::string id;
  std::shared_ptr<MessageQ> q;
};

using NestedMap = std::map<std::shared_ptr<MessageQ>, NestedInfo>;

class Module;

class CloseMessage : public Message {
  std::string_view id() override { return "<CLOSE>"; }
};

class StopMessage : public Message {
  std::string_view id() override { return "<STOP>"; }
};

class LastAckMessage : public Message {
  std::string_view id() override { return "<LASTACK>"; }

 public:
  LastAckMessage(std::unique_ptr<Module> module)
      : m_module{std::move(module)} {};

 private:
  std::unique_ptr<Module> m_module = nullptr;
};

class Module {
 public:
  Module();
  virtual ~Module();

  std::weak_ptr<MessageQ> launchAsRoot(ConfigElement* config = nullptr);
  std::weak_ptr<MessageQ> launchAsNested(std::weak_ptr<MessageQ> parentQ,
                                         ConfigElement* config = nullptr);

 protected:
  ConfigElement* getConfig();
  TaskConfig* getTaskConfig();

  bool sendToSelf(std::unique_ptr<Message> m, bool atFront = false) {
    return atFront ? m_selfQ->enqueueFront(std::move(m), 0ms)
                   : m_selfQ->enqueue(std::move(m), 0ms);
  }

  bool sendToParent(std::unique_ptr<Message> m) {
    return m_selfQ->enqueue(std::move(m), 0ms);
  }

  std::unique_ptr<Message> nextMessage(Timeout timeout = -1ms);

  virtual bool initModule() = 0;
  virtual bool startModule() = 0;
  virtual bool runModule() = 0;
  virtual bool cleanupModule() = 0;

  virtual size_t qSize() { return -1; }

 private:
  void launch();
  void thread();

  void registerNested(std::unique_ptr<Module> module);
  void unregisterNested(std::unique_ptr<Module> module);

  // MessageQ used to send this module messages. Can be shared to other Modules
  // hence the shared_ptr.
  std::shared_ptr<MessageQ> m_selfQ{};

  // MessageQ used to send the parent in the module hierarchy a message. This
  // is typically used for internal reporting and for nested helpers that run
  // under a manager module.
  std::shared_ptr<MessageQ> m_parentQ{};

  // This module's config element. The config manager owns the element.
  ConfigElement* m_config = nullptr;

  // Stores any modules launched as nested modules under this module. Using a
  // unique_ptr since we want it to stay accessible (even if not messageable)
  // at least as long as this module is alive. When closing, we'll want to wait
  // for all nested modules to stop (join their threads)
  std::vector<std::unique_ptr<Module>> m_nested;

  // Set once the module receives a <CLOSE> message and has begun shutting down.
  bool m_closing = false;

  // Flag that nested modules have been closed after the <CLOSE> message has
  // been handled.
  bool m_nestedClosed = false;

  // set once the module passes through the <STOP> message handling
  // the <STOP> message is a "fake" message used for internal tracking and user
  // implementation interaction but once this is set, nextMessage() should not
  // be called again.
  bool m_stopped = false;
};

}  // namespace Volatus

#endif  // Module_hpp_
