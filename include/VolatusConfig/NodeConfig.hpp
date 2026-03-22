#ifndef NodeConfig_hpp_
#define NodeConfig_hpp_

#include "ConfigElement.hpp"
#include "ConfigTypes.hpp"
#include "TaskConfig.hpp"

namespace Volatus {

class NodeConfig : public ConfigElement {
 public:
  NodeConfig(Config::Element* elem);
  NodeConfig(const ConfigElement& cfgElem);

  uint32_t getNodeId();
  bool getDebug();
  NetworkConfig getNetworkConfig();
  std::vector<std::string> getGroups();
  std::vector<TaskConfig> getTasks();
};

}  // namespace Volatus

#endif  // NodeConfig_hpp_
