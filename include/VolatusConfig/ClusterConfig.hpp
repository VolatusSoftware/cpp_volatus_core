#ifndef ClusterConfig_hpp_
#define ClusterConfig_hpp_

#include <map>

#include "ConfigElement.hpp"
#include "ConfigTypes.hpp"
#include "NodeConfig.hpp"

namespace Volatus {

using TargetGroups = std::map<std::string, uint32_t>;

class ClusterConfig : public ConfigElement {
 public:
  ClusterConfig(Config::Element* elem);
  ClusterConfig(const ConfigElement& cfgElem);

  std::vector<NodeConfig> getNodes();

  std::optional<Endpoint> getDiscoveryEndpoint();
  std::optional<TelemetryRouting> getTelemetryRouting();

  TargetGroups getTargetGroups();
};

}  // namespace Volatus

#endif  // ClusterConfig_hpp_
