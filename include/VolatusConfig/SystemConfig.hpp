#ifndef SystemConfig_hpp_
#define SystemConfig_hpp_

#include "ConfigElement.hpp"

namespace Volatus {

  class ClusterConfig;

class SystemConfig : public ConfigElement {
 public:
  SystemConfig(Config::Element* elem);
  SystemConfig(const ConfigElement& cfgElem);

  std::vector<ClusterConfig> getClusters();
};

}  // namespace Volatus

#endif  // SystemConfig_hpp_
