#ifndef ConfigManager_hpp_
#define ConfigManager_hpp_

#include <vector>

#include "Element.hpp"

namespace Config {

class Manager {
public:
    Manager() = default;
    ~Manager() = default;

private:
    std::vector<Element> m_elements;
    std::vector<int> m_freeIndex;
};

}; //namespace

#endif //ConfigManager_hpp_
