#ifndef ConfigTypes_hpp_
#define ConfigTypes_hpp_

#include <map>
#include <string>
#include <vector>
#include <set>

#include "Value.hpp"

namespace Config {
class Manager;
class Element;

using Hierarchy = std::vector<std::string>;
using MetaMap = std::map<std::string, Value>;
using NamedChildMap = std::map<std::string, Element*>;
using Path = std::filesystem::path;

static const std::set<std::string> truthful = {"1", "t", "T", "true", "True", "y", "Y", "yes", "Yes"};

}  // namespace Config

#endif  // ConfigTypes_hpp_
