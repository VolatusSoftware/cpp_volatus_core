#ifndef VolatusConfigTypes_hpp_
#define VolatusConfigTypes_hpp_

#include <array>
#include <string>
#include <type_traits>

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

}  // namespace Volatus

#endif  // VolatusConfigTypes_hpp_
