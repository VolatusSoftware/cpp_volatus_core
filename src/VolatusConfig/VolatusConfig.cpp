#include "VolatusConfig/VolatusConfig.hpp"

#include "ConfigTree/ConfigJson.hpp"

namespace Volatus {

VolatusConfig::VolatusConfig() : m_mgr{std::make_unique<Config::Manager>()} {}

VolatusConfig::VolatusConfig(std::unique_ptr<Config::Manager> cm) : m_mgr{std::move(cm)} {}

// Destructor
VolatusConfig::~VolatusConfig() {}

// Copy constructor
VolatusConfig::VolatusConfig(const VolatusConfig& other) {}

// Move constructor
VolatusConfig::VolatusConfig(VolatusConfig&& from) noexcept {}

// Copy Assignment
VolatusConfig& VolatusConfig::operator=(const VolatusConfig& other) {
  return *this;
}

// Move Assignment
VolatusConfig& VolatusConfig::operator=(VolatusConfig&& from) {
  return *this;
}

SystemConfig VolatusConfig::getSystem() {
  Config::Lookup systemLookup;
  addTypeLookup(systemLookup, ConfigType::VL_System);

  auto res = m_mgr->lookupElements(systemLookup);

  if (res.size() == 0) {
    throw std::runtime_error("System element not found in config tree.");
  } else if (res.size() > 1) {
    throw std::runtime_error("Multiple System elements found in config tree.");
  }

  return res[0];
}

VolatusConfig loadConfig(const Config::Path& path) {
  Config::Json jsonLoader{path};
  auto mgr = std::make_unique<Config::Manager>();

  jsonLoader.load(*mgr.get());

  VolatusConfig cfg{std::move(mgr)};

  return cfg;
}

}  // namespace Volatus
