#ifndef volatusconfig_h_
#define volatusconfig_h_

#include "ConfigTree/Manager.hpp"
#include "ConfigTypes.hpp"
#include "SystemConfig.hpp"

namespace Volatus {

inline Config::Lookup& addTypeLookup(Config::Lookup& lookup, ConfigType type) {
  return lookup.addMatchMeta(configTypeString(type));
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

  /**
   * Loads configuration from the specified path,
   */
  VolatusConfig(Config::Path path);

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

VolatusConfig&& loadConfig(Config::Path);

}  // namespace Volatus

#endif  // volatusconfig_h_
