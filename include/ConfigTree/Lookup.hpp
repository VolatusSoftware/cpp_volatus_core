#ifndef Lookup_hpp_
#define Lookup_hpp_

#include <map>
#include <string>
#include <vector>

#include "Types.hpp"

namespace Config {
struct MatchMeta {
  std::string name{};
  Value value{};
};

extern const Value noValue;

class Lookup {
 public:
  Lookup& matchName(std::string_view name);

  Lookup& addMatchMeta(std::string_view name, const Value& value = noValue);

  Lookup& stopRecursePastMatch();

  bool recursePastMatch() const { return !m_stopRecursePastMatch; }

  bool checkMatch(const std::string& name, const MetaMap& meta) const;

  Lookup& reset();

 private:
  std::string_view m_nameMatch{};
  std::vector<MatchMeta> m_metaMatch{};
  bool m_stopRecursePastMatch = false;
};

}  // namespace Config

#endif  // Lookup_hpp_
