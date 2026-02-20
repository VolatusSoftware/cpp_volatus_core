#ifndef ConfigManager_hpp_
#define ConfigManager_hpp_

#include <array>
#include <cassert>
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
  Element* obtainElement(const std::string& name, bool canCreate = true);

  Element* createElement(const std::string_view name,
                         Element* parent = nullptr);

  size_t size() { return m_elements.size(); }

 private:
  std::map<Hierarchy, Element> m_elements{};

  /**
   * There is a root element outside of m_elements that tracks all of the
   * unparented elements within m_elements as a convenience for lookups.
   */
  Element m_root{true};
};

};  // namespace Config

#endif  // ConfigManager_hpp_
