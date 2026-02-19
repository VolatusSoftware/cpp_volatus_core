#ifndef Lookup_hpp_
#define Lookup_hpp_

#include <vector>
#include <string>
#include <map>

#include "Types.hpp"

namespace Config
{
    struct MatchMeta
    {
        const std::string &name{};
        const Value value{};
    };

    class Lookup
    {
    public:
        Lookup &matchName(std::string_view name);

        Lookup &addMatchMetaName(const std::string &name);

        Lookup &addMatchMeta(const std::string &name, const Value &value);

        bool checkMatch(const std::string &name, const MetaMap &meta) const;

    private:
        std::string_view m_nameMatch{};
        std::vector<MatchMeta> m_metaMatch{};
    };

    Lookup &Lookup::matchName(std::string_view name)
    {
        m_nameMatch = name;
        return *this;
    }

    Lookup &Lookup::addMatchMetaName(const std::string &name)
    {
        m_metaMatch.push_back({name, UnknownType{}});
        return *this;
    }

    Lookup &Lookup::addMatchMeta(const std::string &name, const Value &value)
    {
        m_metaMatch.push_back({name, value});
        return *this;
    }

    bool Lookup::checkMatch(const std::string &name, const MetaMap &meta) const
    {
        bool matchName = !m_nameMatch.empty();
        bool matchMeta = !m_metaMatch.empty();

        if (!(matchName || matchMeta))
        {
            return false;
        }

        if (matchName && m_nameMatch.compare(name) != 0)
        {
            return false;
        }

        if (matchMeta)
        {
            for (auto it = m_metaMatch.begin(); it != m_metaMatch.end(); ++it)
            {
                auto elMeta = meta.find(it->name);
                if (elMeta == meta.end())
                {
                    return false;
                }

                auto matchMetaType = it->value.getType();

                if (matchMetaType != ValueType::UNKNOWN)
                {
                    auto otherType = elMeta->second.getType();
                    if (matchMetaType != otherType)
                    {
                        return false;
                    }

                    // type is set and matches, compare values
                    if (it->value != elMeta->second)
                    {
                        return false;
                    }
                }
            }
        }

        // survived all the comparisons/checks, must match.
        return true;
    }
}

#endif // Lookup_hpp_
