#include "ConfigTree/Element.hpp"

namespace Config {

std::string hierarchyString(const Hierarchy& hierarchy) {
  std::stringstream ss{};

  bool first = true;
  for (auto it = hierarchy.begin(); it != hierarchy.end(); ++it) {
    if (!first) {
      ss << ":";
    } else {
      first = false;
    }

    ss << *it;
  }

  return ss.str();
}

std::string Element::hierarchyString() {
  return Config::hierarchyString(getHierarchy());
}

void Element::setParent(Element* parent) {
  if (m_parent) {
    m_parent->removeChild(this);
  }

  m_parent = parent;
}

Element* Element::lookupAncestor(const Lookup& lookup) {
  Element* el = m_parent;

  while (el) {
    if (el->matchesLookup(lookup)) {
      return el;
    }
  }

  return nullptr;
}

std::vector<Element*> Element::lookupDescendents(const Lookup& lookup) {
  // stack of elements to continue searching for matches
  std::vector<Element*> toCheck{};

  // to store elements that match the lookup
  std::vector<Element*> matches{};

  // start with all immediate children on the stack
  for (auto it = m_children.begin(); it != m_children.end(); ++it) {
    toCheck.push_back(it->second);
  }

  while (!toCheck.empty()) {
    Element* el = toCheck.back();
    toCheck.pop_back();

    bool recurse = true;

    if (el->matchesLookup(lookup)) {
      matches.push_back(el);
      if (!lookup.recursePastMatch()) {
        recurse = false;
      }
    }

    if (recurse) {
      std::vector<Element*> children = el->getChildren();
      for (auto it = children.begin(); it != children.end(); ++it) {
        toCheck.push_back(*it);
      }
    }
  }

  return matches;
}

Hierarchy Element::getHierarchy() {
  Hierarchy hierarchy{};

  Element* el = this;

  while (el && !el->m_isRoot) {
    hierarchy.push_back(el->getName());
    el = el->getParent();
  }

  std::reverse(hierarchy.begin(), hierarchy.end());

  return hierarchy;
}

Element* Element::lookupChild(const std::string_view name) {
  // comparing string_view to string so use find_if instead of vector.find
  auto it = std::find_if(m_children.begin(), m_children.end(),
                         [&](std::pair<const std::string&, Element*> c) {
                           return c.second->getName() == name;
                         });

  if (it != m_children.end()) {
    return it->second;
  }

  return nullptr;
}

void Element::setObjectType() { m_value.setObjectType(); }

void Element::setArrayType() { m_value.setArrayType(); }

std::vector<Element*> Element::getChildren() {
  std::vector<Element*> children{};
  for (auto it = m_children.begin(); it != m_children.end(); ++it) {
    children.push_back(it->second);
  }

  return children;
}

void Element::addChild(Element* el) {
  if (el) {
    m_children.insert_or_assign(std::string(el->getName()), el);
    el->setParent(this);
  }
}

bool Element::removeChild(Element* el) {
  bool found = false;

  if (el) {
    auto it = m_children.find(el->getName());
    if (it != m_children.end()) {
      m_children.erase(it);
      it->second->setParent(nullptr);
      found = true;
    }
  }

  return found;
}

Value* Element::lookupMeta(const std::string& metaName) {
  auto it = m_meta.find(metaName);
  if (it != m_meta.end()) {
    return &it->second;
  }

  return nullptr;
}

}  // namespace Config
