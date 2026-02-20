#include "ConfigTree/Lookup.hpp"

using namespace Config;

Lookup& Lookup::reset() {
  m_nameMatch = "";
  m_metaMatch.clear();
  m_stopRecursePastMatch = false;

  return *this;
}

Lookup& Lookup::stopRecursePastMatch() {
  m_stopRecursePastMatch = true;
  return *this;
}

Lookup& Lookup::matchName(std::string_view name) {
  m_nameMatch = name;
  return *this;
}

Lookup& Lookup::addMatchMeta(const std::string& name, const Value& value) {
  m_metaMatch.push_back({name, value});
  return *this;
}

bool Lookup::checkMatch(const std::string& name, const MetaMap& meta) const {
  bool matchName = !m_nameMatch.empty();
  bool matchMeta = !m_metaMatch.empty();

  if (!(matchName || matchMeta)) {
    return false;
  }

  if (matchName && m_nameMatch.compare(name) != 0) {
    return false;
  }

  if (matchMeta) {
    for (auto it = m_metaMatch.begin(); it != m_metaMatch.end(); ++it) {
      auto elMeta = meta.find(it->name);
      if (elMeta == meta.end()) {
        return false;
      }

      auto matchMetaType = it->value.getType();

      if (matchMetaType != ValueType::UNKNOWN) {
        auto otherType = elMeta->second.getType();
        if (matchMetaType != otherType) {
          return false;
        }

        // type is set and matches, compare values
        if (it->value != elMeta->second) {
          return false;
        }
      }
    }
  }

  // survived all the comparisons/checks, must match.
  return true;
}
