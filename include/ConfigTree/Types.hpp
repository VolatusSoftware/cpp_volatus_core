#ifndef ConfigTypes_hpp_
#define ConfigTypes_hpp_

#include <vector>
#include <string>
#include <map>

#include "Value.hpp"

namespace Config
{
    class Manager;
    class Element;

    using Hierarchy = std::vector<std::string>;
    using MetaMap = std::map<std::string, Value>;
    using NamedChildMap = std::map<std::string, Element*>;
    using Path = std::filesystem::path;
}

#endif //ConfigTypes_hpp_
