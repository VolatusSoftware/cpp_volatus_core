#ifndef SystemConfig_hpp_
#define SystemConfig_hpp_

#include "ConfigElement.hpp"

namespace Volatus {

class SystemConfig : public ConfigElement {
 public:
  SystemConfig(Config::Element* elem);
  SystemConfig(const ConfigElement& cfgElem);
};

}  // namespace Volatus

#endif  // SystemConfig_hpp_
