#include "ConfigTree/Manager.hpp"

namespace Config {

Element* Manager::createElement(const std::string_view name, Element* parent) {
  if (!parent) {
    parent = &m_root;
  }

  // Check if duplicated name
  Element* el = parent->lookupChild(name);
  if (el) {
    // cannot have 2 children with the same name
    return nullptr;
  }

  Hierarchy hierarchy = parent->getHierarchy();
  hierarchy.emplace_back(name);

  auto newEl = m_elements.emplace(hierarchy, name);
  if (!newEl.second) {
    // insertion failed
    return nullptr;
  }

  el = &(newEl.first->second);
  parent->addChild(el);

  el->setObjectType();  // default new elements as object container

  return el;
}

Element* Manager::obtainElement(const std::string& name, bool canCreate) {
  Element* child = m_root.lookupChild(name);

  if (!child && canCreate) {
    child = createElement(name);
  }

  return child;
}

Element* Manager::obtainElement(const Hierarchy& hierarchy, bool canCreate) {
  assert(hierarchy.size() > 0);

  Element* el = &m_root;
  Element* child = nullptr;

  for (auto it = hierarchy.begin(); it != hierarchy.end(); ++it) {
    std::string name = *it;
    child = el->lookupChild(name);
    if (!child) {
      if (canCreate) {
        child = createElement(name, el);
      } else {
        return nullptr;
      }
    }

    el = child;
  }

  return child;
}

std::vector<Element*> Manager::lookupElements(const Lookup& lookup) {
  return m_root.lookupDescendents(lookup);
}

}  // namespace Config
