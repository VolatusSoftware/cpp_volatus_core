#ifndef ConfigElement_hpp_
#define ConfigElement_hpp_

#include <string>
#include <stdint.h>
#include <vector>
#include <map>
#include <variant>
#include <filesystem>
#include <algorithm>
#include <optional>
#include <sstream>
#include <iterator>

#include "Value.hpp"
#include "Lookup.hpp"

namespace Config
{

    std::string hierarchyString(const Hierarchy &hierarchy)
    {
        std::stringstream ss{};

        bool first = true;
        for (auto it = hierarchy.begin(); it != hierarchy.end(); ++it)
        {
            if (!first)
            {
                ss << ":";
            }
            else
            {
                first = false;
            }

            ss << *it;
        }

        return ss.str();
    }

    class Element
    {
    public:
        Element(std::string_view name) : m_name{name} {}

        template <typename T>
        Element(std::string_view name, T value);

        ~Element() = default;

        std::string getName() { return m_name; }

        Manager *getOwner() { return m_owner; }

        void setOwner(Manager *owner) { m_owner = owner; }

        // Element Value proxy methods
        ValueType getType() { return m_value.getType(); }
        std::string_view typeString() { return m_value.typeString(); }
        bool isType(ValueType type) { return m_value.isType(type); }

        template <typename T>
        void setValue(const T &value) { m_value.setValue<T>(value); }

        template <typename T>
        const T &getValue() { return m_value.getValue<T>(); }

        void setParent(Element *parent) { m_parent = parent; }

        Element *getParent() { return m_parent; }

        void addChild(Element *el);
        bool removeChild(Element *el);

        Element *lookupChild(const std::string &name);

        bool matchesLookup(const Lookup& lookup) { return lookup.checkMatch(m_name, m_meta); }

        std::vector<Element *> getChildren(); // { return m_children.; }

        Value *lookupMeta(const std::string &metaName);

        template <typename T>
        bool setMetaValue(const std::string &metaName, const T &value);

        Hierarchy getHierarchy();

        std::string hierarchyString();

    private:
        std::string m_name{};

        Manager *m_owner = nullptr;
        Value m_value{};

        // Elements do not own their relatives (Manager does)
        Element *m_parent = nullptr;
        NamedChildMap m_children{};

        MetaMap m_meta{};
    };

    Hierarchy Element::getHierarchy()
    {
        Hierarchy hierarchy{};

        Element *el = this;

        while (el)
        {
            hierarchy.push_back(el->getName());
            el = el->getParent();
        }

        std::reverse(hierarchy.begin(), hierarchy.end());

        return hierarchy;
    }

    Element *Element::lookupChild(const std::string &name)
    {
        auto it = m_children.find(name);

        if (it != m_children.end())
        {
            return it->second;
        }

        return nullptr;
    }

    std::vector<Element *> Element::getChildren()
    {
        std::vector<Element *> children{};
        for (auto it = m_children.begin(); it != m_children.end(); ++it)
        {
            children.push_back(it->second);
        }

        return children;
    }

    void Element::addChild(Element *el)
    {
        if (el)
        {
            m_children.insert_or_assign(std::string(el->getName()), el);
            el->setParent(this);
        }
    }

    bool Element::removeChild(Element *el)
    {
        bool found = false;

        if (el)
        {
            auto it = m_children.find(el->getName());
            if (it != m_children.end())
            {
                m_children.erase(it);
                it->second->setParent(nullptr);
                found = true;
            }
        }

        return found;
    }

    Value *Element::lookupMeta(const std::string &metaName)
    {
        auto it = m_meta.find(metaName);
        if (it != m_meta.end())
        {
            return &it->second;
        }

        return nullptr;
    }

    template <typename T>
    bool Element::setMetaValue(const std::string &metaName, const T &value)
    {
        Value val;
        val.setValue(value);

        auto result = m_meta.insert_or_assign(metaName, val);
        return result.second;
    }

}; // namespace

#endif // ConfigElement_hpp_
