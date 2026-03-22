#include "VolatusConfig/VolatusConfig.hpp"

namespace Volatus {

NodeConfig::NodeConfig(Config::Element* elem) : ConfigElement{elem} {}

uint32_t NodeConfig::getNodeId() {
  auto nodeId = get()->lookupChild("Node_ID");
  if (nodeId) {
    return nodeId->getValue<uint32_t>();
  }

  throw std::runtime_error("Node_ID is not set.");
}

bool NodeConfig::getDebug() {
  auto debug = get()->lookupChild("Debug");
  if (debug) {
    return debug->getValue<bool>();
  }

  // Element is optional, if doesn't exist default to not debug mode.
  return false;
}

NetworkConfig NodeConfig::getNetworkConfig() {
  NetworkConfig netCfg{};

  auto net = get()->lookupChild("Network");
  if (net) {
    auto elem = net->lookupChild("Bind_Address");
    if (elem) {
      netCfg.bindAddress = elem->getValue<std::string>();
    }

    elem = net->lookupChild("Announce_Interval");
    if (elem) {
      netCfg.announceInterval = elem->getValue<double>();
    }

    elem = net->lookupChild("HTTP_Port");
    if (elem) {
      netCfg.httpPort = elem->getValue<uint16_t>();
    }

    auto tcp = net->lookupChild("TCP");
    if (tcp) {
      elem = tcp->lookupChild("Address");
      if (!elem) {
        throw std::runtime_error("TCP element must contain Address element");
      }
      netCfg.tcp.endpoint.address = elem->getValue<std::string>();

      elem = tcp->lookupChild("Port");
      if (!elem) {
        throw std::runtime_error("TCP element must contain Port element");
      }
      netCfg.tcp.endpoint.port = elem->getValue<uint16_t>();

      elem = tcp->lookupChild("Server");
      if (elem) {
        netCfg.tcp.isServer = elem->getValue<bool>();
      }
    }
  }

  return netCfg;
}

std::vector<std::string> NodeConfig::getGroups() {
  std::vector<std::string> groups{};

  auto elem = get()->lookupChild("Groups");
  if (elem) {
    auto children = elem->getChildren();
    for (auto it = children.begin(); it != children.end(); ++it) {
      groups.push_back((*it)->getValue<std::string>());
    }
  }

  return groups;
}

std::vector<TaskConfig> NodeConfig::getTasks() {
  Config::Lookup taskLookup;
  addTypeLookup(taskLookup, ConfigType::VL_Task);

  auto elems = get()->lookupDescendents(taskLookup);
  std::vector<TaskConfig> tasks{};

  for (auto it = elems.begin(); it != elems.end(); ++it) {
    tasks.emplace_back(*it);
  }

  return tasks;
}

}  // namespace Volatus
