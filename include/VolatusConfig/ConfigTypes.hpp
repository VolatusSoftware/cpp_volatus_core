#ifndef VolatusConfigTypes_hpp_
#define VolatusConfigTypes_hpp_

#include <array>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <stdint.h>
#include <format>

#include "ConfigTree/Types.hpp"

namespace Volatus {

enum class ConfigType {
  UNKNOWN,
  VL_System,
  VL_Cluster,
  VL_Node,
  VL_Task,
  VL_Group,
  VL_Channel,
  VL_Scaling,
  VL_Sensor_List,
  VL_Scale,

  VL_TYPES_END
};

using ConfigTypeInt = std::underlying_type<ConfigType>::type;

constexpr ConfigTypeInt toInt(ConfigType type) {
  return static_cast<ConfigTypeInt>(type);
}

constexpr std::array<std::string, static_cast<ConfigTypeInt>(
                                      toInt(ConfigType::VL_TYPES_END))>
    configTypeStrings = {
        "Unknown",  "VL_System",  "VL_Cluster", "VL_Node",        "VL_Task",
        "VL_Group", "VL_Channel", "VL_Scaling", "VL_Sensor_List", "VL_Scale"};

inline std::string_view configTypeString(ConfigType type) {
  return configTypeStrings[static_cast<ConfigTypeInt>(type)];
}

struct Endpoint {
  std::string address{};
  uint16_t port{};
};

inline std::string endpointString(const Endpoint& endpt) {
  return std::format("{}:{}", endpt.address, endpt.port);
}

enum class TelemetryRouting {
  UNKNOWN,
  Multicast,
  Unicast,

  END
};

using TelemetryRoutingInt = std::underlying_type<TelemetryRouting>::type;

constexpr TelemetryRoutingInt toInt(TelemetryRouting routing) {
  return static_cast<TelemetryRoutingInt>(routing);
}

constexpr std::array<std::string, static_cast<TelemetryRoutingInt>(
                                      toInt(TelemetryRouting::END))>
    telemetryRoutingStrings = {"Unknown", "Multicast", "Unicast"};

inline std::string_view telemetryRoutingString(TelemetryRouting routing) {
  return telemetryRoutingStrings[static_cast<TelemetryRoutingInt>(routing)];
}

static const std::unordered_map<std::string, TelemetryRouting>
    telemetryRoutingMap = {{"Multicast", TelemetryRouting::Multicast},
                           {"Unicast", TelemetryRouting::Unicast}};

inline TelemetryRouting telemetryRouting(const std::string& string) {
  auto it = telemetryRoutingMap.find(string);
  if (it != telemetryRoutingMap.end()) {
    return it->second;
  }

  return TelemetryRouting::UNKNOWN;
}

struct EventsConfig {
  Config::Path loggingPath{};
};

struct TCPConfig {
  Endpoint endpoint{};
  bool isServer{};
};

struct NetworkConfig {
  std::string bindAddress{};
  double announceInterval{};
  TCPConfig tcp{};
  uint16_t httpPort{};
};

}  // namespace Volatus

#endif  // VolatusConfigTypes_hpp_
