#ifndef ConfigElement_hpp_
#define ConfigElement_hpp_

#include <stdint.h>

#include <algorithm>
#include <filesystem>
#include <iterator>
#include <map>
#include <optional>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

#include "Lookup.hpp"
#include "Value.hpp"

namespace Config {

std::string hierarchyString(const Hierarchy& hierarchy);

class Element {
 public:
  Element(std::string_view name) : m_name{name} {}

  Element(bool isRoot) : m_isRoot{isRoot}, m_name{"<ROOT>"} {};

  template <typename T>
  Element(std::string_view name, T value);

  ~Element() = default;

  std::string getName() { return m_name; }

  Manager* getOwner() { return m_owner; }

  void setOwner(Manager* owner) { m_owner = owner; }

  // Element Value proxy methods
  ValueType getType() { return m_value.getType(); }
  std::string_view typeString() { return m_value.typeString(); }
  bool isType(ValueType type) { return m_value.isType(type); }

  template <typename T>
  void setValue(const T& value) {
    m_value.setValue<T>(value);
  }

  template <typename T>
  const T& getValue() {
    return m_value.getValue<T>();
  }

  void setParent(Element* parent);  // { m_parent = parent; }

  Element* getParent() { return m_parent; }

  void addChild(Element* el);
  bool removeChild(Element* el);

  Element* lookupChild(const std::string_view name);

  bool matchesLookup(const Lookup& lookup) {
    return lookup.checkMatch(m_name, m_meta);
  }

  std::vector<Element*> getChildren();  // { return m_children.; }

  Value* lookupMeta(const std::string& metaName);

  template <typename T>
  bool setMetaValue(const std::string& metaName, const T& value);

  Hierarchy getHierarchy();

  std::string hierarchyString();

  void setObjectType();
  void setArrayType();

  Element* lookupAncestor(const Lookup& lookup);
  std::vector<Element*> lookupDescendents(const Lookup& lookup);

 private:
  std::string m_name{};

  bool m_isRoot{};

  Manager* m_owner = nullptr;
  Value m_value{};

  // Elements do not own their relatives (Manager does)
  Element* m_parent = nullptr;
  NamedChildMap m_children{};

  MetaMap m_meta{};
};

template <typename T>
bool Element::setMetaValue(const std::string& metaName, const T& value) {
  Value val;
  val.setValue(value);

  auto result = m_meta.insert_or_assign(metaName, val);
  return result.second;
}

};  // namespace Config

#endif  // ConfigElement_hpp_
