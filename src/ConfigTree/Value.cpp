#include "ConfigTree/Value.hpp"

namespace Config {

std::array<std::string, static_cast<ValueTypeInt>(toInt(ValueType::TYPES_END))>
    valueTypeStrings{"Unknown", "Object", "Array",  "Bool", "I8",  "U8",
                     "I16",     "U16",    "I32",    "U32",  "I64", "U64",
                     "SGL",     "DBL",    "String", "Path"};

bool operator==(const Value& lhs, const Value& rhs) {
  if (lhs.getType() == rhs.getType()) {
    switch (lhs.getType()) {
      case ValueType::ARRAY:
      case ValueType::OBJECT:
        return false;  // only support comparing scalar types

      case ValueType::BOOL:
        return equals<bool>(lhs, rhs);

      case ValueType::DBL:
        return equals<double>(lhs, rhs);

      case ValueType::I16:
        return equals<int16_t>(lhs, rhs);

      case ValueType::I32:
        return equals<int32_t>(lhs, rhs);

      case ValueType::I64:
        return equals<int64_t>(lhs, rhs);

      case ValueType::I8:
        return equals<int8_t>(lhs, rhs);

      case ValueType::PATH:
        return equals<Path>(lhs, rhs);

      case ValueType::SGL:
        return equals<float>(lhs, rhs);

      case ValueType::STRING:
        return equals<std::string>(lhs, rhs);

      case ValueType::U16:
        return equals<uint16_t>(lhs, rhs);

      case ValueType::U32:
        return equals<uint32_t>(lhs, rhs);

      case ValueType::U64:
        return equals<uint64_t>(lhs, rhs);

      case ValueType::U8:
        return equals<uint8_t>(lhs, rhs);
    }
  }

  return false;
}

bool operator!=(const Value& lhs, const Value& rhs) { return !(lhs == rhs); }

}  // namespace Config
