#include <format>

#include "VolatusConfig/VolatusConfig.hpp"

namespace Volatus {

ClusterConfig::ClusterConfig(Config::Element* elem) : ConfigElement{elem} {}

std::vector<NodeConfig> ClusterConfig::getNodes() {
  Config::Lookup nodeLookup;
  addTypeLookup(nodeLookup, ConfigType::VL_Node);

  auto elems = get()->lookupDescendents(nodeLookup);
  std::vector<NodeConfig> nodes{};

  for (auto it = elems.begin(); it != elems.end(); ++it) {
    nodes.emplace_back(*it);
  }

  return nodes;
}

std::optional<Endpoint> ClusterConfig::getDiscoveryEndpoint() {
  auto discovery = get()->lookupChild("Discovery");
  if (discovery) {
    auto address = discovery->lookupChild("Address");
    auto port = discovery->lookupChild("Port");

    if (!address || !port) {
      throw std::runtime_error(std::format(
          "Invalid Discovery configuration in cluster '{}'.", getName()));
    }

    return Endpoint{address->getValue<std::string>(),
                    port->getValue<uint16_t>()};
  }

  return {};
}

std::optional<TelemetryRouting> ClusterConfig::getTelemetryRouting() {
    auto telem = get()->lookupChild("Telemetry");
    if (telem) {
        auto routing = telem->lookupChild("Routing");
        if (routing) {
            return telemetryRouting(routing->getValue<std::string>());
        }
    }

    return {};
}

TargetGroups ClusterConfig::getTargetGroups() {
    TargetGroups targetGroups{};

    auto groups = get()->lookupChild("Groups");
    if (groups) {
        auto children = groups->getChildren();
        for (auto it = children.begin(); it != children.end(); ++it) {
            targetGroups.insert({(*it)->getName(), (*it)->getValue<uint32_t>()});
        }
    }

    return targetGroups;
}

}  // namespace Volatus
