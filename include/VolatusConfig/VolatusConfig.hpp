#ifndef volatusconfig_h_
#define volatusconfig_h_

#include "ConfigTree/Manager.hpp"
#include "ConfigTypes.hpp"
#include "SystemConfig.hpp"
#include "ClusterConfig.hpp"
#include "NodeConfig.hpp"

namespace Volatus {

inline Config::Lookup& addTypeLookup(Config::Lookup& lookup, ConfigType type) {
  return lookup.addMatchMeta("VL_Type", configTypeString(type));
}

inline Config::Lookup& addMetaLookup(Config::Lookup& lookup, ConfigType type,
                                     const Config::Value& value) {
  return lookup.addMatchMeta(configTypeString(type), value);
}

class VolatusConfig {
 public:
  /**
   * Creates an empty config for building programmatically or loading later on
   */
  VolatusConfig();

  VolatusConfig(std::unique_ptr<Config::Manager> cm);

  // Destructor
  ~VolatusConfig();

  // Copy constructor
  VolatusConfig(const VolatusConfig& other);

  // Move constructor
  VolatusConfig(VolatusConfig&& from) noexcept;

  // Copy Assignment
  VolatusConfig& operator=(const VolatusConfig& other);

  // Move Assignment
  VolatusConfig& operator=(VolatusConfig&& from);

  SystemConfig getSystem();

 private:
  std::unique_ptr<Config::Manager> m_mgr;
};

VolatusConfig loadConfig(const Config::Path& path);

}  // namespace Volatus

#endif  // volatusconfig_h_
