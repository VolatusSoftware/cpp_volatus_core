#ifndef ConfigManager_hpp_
#define ConfigManager_hpp_

#include <array>
#include <map>
#include <string>
#include <vector>

#include "Element.hpp"

namespace Config {

class Manager {
 public:
  Manager() = default;
  ~Manager() = default;

  /**
   * Returns the specified element if it already exists or creates as much
   * of the specified hierarchy as needed and creates a new element that will
   * be returned.
   */
  Element* obtainElement(const Hierarchy& hierarchy, bool canCreate = true);

  Element* createElement(const std::string& name, Element* parent = nullptr);

  std::vector<Element*> lookupDescendents(const Lookup& lookup);

 private:
  std::map<std::vector<std::string>, Element> m_elements{};
};

};  // namespace Config

#endif  // ConfigManager_hpp_
