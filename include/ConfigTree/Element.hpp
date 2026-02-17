#ifndef ConfigElement_hpp_
#define ConfigElement_hpp_

#include <string>
#include <stdint.h>
#include <vector>
#include <variant>
#include <filesystem>

namespace Config {

//Store a monostate when the type is unknown.
using UnknownType = std::monostate;
using Path = std::filesystem::path;

using ElementValue = std::variant<
    UnknownType,
    bool,
    int8_t,
    uint8_t,
    int16_t,
    uint16_t,
    int32_t,
    uint32_t,
    int64_t,
    uint64_t,
    float,
    double,
    std::string,
    Path
>;

// These values must match the ordering of the ElementValue alternatives above
enum class ValueType {
    UNKNOWN,
    BOOL,
    I8,
    U8,
    I16,
    U16,
    I32,
    U32,
    I64,
    U64,
    SGL,
    DBL,
    STRING,
    PATH,

    NUM_TYPES
};

using ValueTypeInt = std::underlying_type<ValueType>::type;

std::array<std::string, static_cast<ValueTypeInt>(ValueType::NUM_TYPES)> valueTypeStrings {
    "Unknown",
    "Bool",
    "I8",
    "U8",
    "I16",
    "U16",
    "I32",
    "U32",
    "I64",
    "U64",
    "SGL",
    "DBL",
    "String",
    "Path"
};

std::string_view valueTypeString(ValueType type) {
    return valueTypeStrings[static_cast<ValueTypeInt>(type)];
}

class Element {
public:
    Element(std::string_view name) : m_name{name} {}
    
    template<typename T>
    Element(std::string_view name, T value);

    ~Element() = default;

    ValueType getType() { return static_cast<ValueType>(m_value.index()); }

    std::string_view typeString() { return valueTypeString(getType()); }

    bool isType(ValueType type) { return getType() == type; }

    std::string_view getName() { return m_name; }

    template<typename T>
    void setValue(const T& value) { m_value = value; }

    template<typename T>
    const T& getValue() { return std::get<T>(m_value); }

private:
    ElementValue m_value{};

    std::string m_name{};

    //Elements do not own their relatives (Manager does), using raw pointers
    Element* m_parent = nullptr;
    std::vector<Element*> m_children{};
};

}; //namespace

#endif //ConfigElement_hpp_
