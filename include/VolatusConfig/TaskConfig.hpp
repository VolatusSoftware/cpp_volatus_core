#ifndef TaskConfig_hpp_
#define TaskConfig_hpp_

#include "ConfigElement.hpp"

namespace Volatus {

class TaskConfig : virtual ConfigElement {
 public:
  TaskConfig(Config::Element* elem);
  TaskConfig(const ConfigElement& cfgElem);

  virtual ~TaskConfig() =default;
};

}

#endif  // TaskConfig_hpp_
