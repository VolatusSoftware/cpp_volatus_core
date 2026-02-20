#ifndef ConfigValue_hpp_
#define ConfigValue_hpp_

#include <stdint.h>

#include <array>
#include <filesystem>
#include <string>
#include <variant>
#include <vector>

namespace Config {

// Store a monostate when the type is unknown.
using UnknownType = std::monostate;

// containers don't store a value in the variant but leverage the tree structure
struct ArrayType {};
struct ObjectType {};

using Path = std::filesystem::path;

// Convenient shortened name for the variant storage with many alternatives
using ElementVariant =
    std::variant<UnknownType, ObjectType, ArrayType, bool, int8_t, uint8_t,
                 int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t, float,
                 double, std::string, Path>;

// These values must match the ordering of the ElementValue alternatives above
enum class ValueType {
  UNKNOWN,
  OBJECT,
  ARRAY,
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

  TYPES_END
};

using ValueTypeInt = std::underlying_type<ValueType>::type;

constexpr ValueTypeInt toInt(ValueType type) {
  return static_cast<ValueTypeInt>(type);
}

extern std::array<std::string,
                  static_cast<ValueTypeInt>(toInt(ValueType::TYPES_END))>
    valueTypeStrings;

inline std::string_view valueTypeString(ValueType type) {
  return valueTypeStrings[static_cast<ValueTypeInt>(type)];
}

/**
 * Wraps a Variant value and adds checking and reporting for specific
 * supported data types.
 */
class Value {
 public:
  template <typename T>
  Value(const T& value) : m_value{value} {}

  Value() : m_value{UnknownType{}} {}

  ValueType getType() const {
    if (m_value.valueless_by_exception()) return ValueType::UNKNOWN;

    return static_cast<ValueType>(m_value.index());
  }

  std::string_view typeString() const { return valueTypeString(getType()); }

  bool isType(ValueType type) const { return getType() == type; }

  template <typename T>
  void setValue(const T& value) {
    m_value = value;
  }

  // overload template function to promote c strings to std::string
  void setValue(const char* value) { setValue(std::string(value)); }

  void setValue(std::string_view value) { setValue(std::string(value)); }

  void setObjectType() { setValue(ObjectType{}); }
  void setArrayType() { setValue(ArrayType{}); }

  template <typename T>
  const T& getValue() {
    return std::get<T>(m_value);
  }

  friend bool operator==(const Value& lhs, const Value& rhs);

  template <typename T>
  friend bool equals(const Value& lhs, const Value& rhs);

 private:
  ElementVariant m_value = UnknownType{};
};

template <typename T>
bool equals(const Value& lhs, const Value& rhs) {
  return std::get<T>(lhs.m_value) == std::get<T>(rhs.m_value);
}

bool operator==(const Value& lhs, const Value& rhs);

bool operator!=(const Value& lhs, const Value& rhs);

}  // namespace Config

#endif  // ConfigValue_hpp_
