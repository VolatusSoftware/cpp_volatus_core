#include "ConfigTree/Value.hpp"

#include "ConfigTree/Types.hpp"

namespace Config {

/*
std::array<std::string, static_cast<ValueTypeInt>(toInt(ValueType::TYPES_END))>
  valueTypeStrings{"Unknown", "Object", "Array",  "Bool", "I8",  "U8",
                   "I16",     "U16",    "I32",    "U32",  "I64", "U64",
                   "SGL",     "DBL",    "String", "Path"};
                   */

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

template <typename To, typename From>
inline To castValue(const ElementVariant& var) {
  return static_cast<To>(std::get<From>(var));
}

template <>
uint8_t Value::getValue<uint8_t>() {
  switch (getType()) {
    case ValueType::U8:
      return std::get<uint8_t>(m_value);
    case ValueType::U16:
      return castValue<uint8_t, uint16_t>(m_value);
    case ValueType::U32:
      return castValue<uint8_t, uint32_t>(m_value);
    case ValueType::U64:
      return castValue<uint8_t, uint64_t>(m_value);
    case ValueType::I8:
      return castValue<uint8_t, int8_t>(m_value);
    case ValueType::I16:
      return castValue<uint8_t, int16_t>(m_value);
    case ValueType::I32:
      return castValue<uint8_t, int32_t>(m_value);
    case ValueType::I64:
      return castValue<uint8_t, int64_t>(m_value);
    case ValueType::SGL:
      return castValue<uint8_t, float>(m_value);
    case ValueType::DBL:
      return castValue<uint8_t, double>(m_value);
    case ValueType::BOOL:
      return std::get<bool>(m_value) ? 1 : 0;
    case ValueType::STRING:
      return std::stoi(std::get<std::string>(m_value));
  }

  throw std::runtime_error(
      std::format("Cannot convert {} to uint8_t", valueTypeString(getType())));
}

template <>
uint16_t Value::getValue<uint16_t>() {
  switch (getType()) {
    case ValueType::U8:
      return castValue<uint16_t, uint8_t>(m_value);
    case ValueType::U16:
      return std::get<uint16_t>(m_value);
    case ValueType::U32:
      return castValue<uint16_t, uint32_t>(m_value);
    case ValueType::U64:
      return castValue<uint16_t, uint64_t>(m_value);
    case ValueType::I8:
      return castValue<uint16_t, int8_t>(m_value);
    case ValueType::I16:
      return castValue<uint16_t, int16_t>(m_value);
    case ValueType::I32:
      return castValue<uint16_t, int32_t>(m_value);
    case ValueType::I64:
      return castValue<uint16_t, int64_t>(m_value);
    case ValueType::SGL:
      return castValue<uint16_t, float>(m_value);
    case ValueType::DBL:
      return castValue<uint16_t, double>(m_value);
    case ValueType::BOOL:
      return std::get<bool>(m_value) ? 1 : 0;
    case ValueType::STRING:
      return std::stoi(std::get<std::string>(m_value));
  }

  throw std::runtime_error(
      std::format("Cannot convert {} to uint16_t", valueTypeString(getType())));
}

template <>
uint32_t Value::getValue<uint32_t>() {
  switch (getType()) {
    case ValueType::U8:
      return castValue<uint32_t, uint8_t>(m_value);
    case ValueType::U16:
      return castValue<uint32_t, uint16_t>(m_value);
    case ValueType::U32:
      return std::get<uint32_t>(m_value);
    case ValueType::U64:
      return castValue<uint32_t, uint64_t>(m_value);
    case ValueType::I8:
      return castValue<uint32_t, int8_t>(m_value);
    case ValueType::I16:
      return castValue<uint32_t, int16_t>(m_value);
    case ValueType::I32:
      return castValue<uint32_t, int32_t>(m_value);
    case ValueType::I64:
      return castValue<uint32_t, int64_t>(m_value);
    case ValueType::SGL:
      return castValue<uint32_t, float>(m_value);
    case ValueType::DBL:
      return castValue<uint32_t, double>(m_value);
    case ValueType::BOOL:
      return std::get<bool>(m_value) ? 1 : 0;
    case ValueType::STRING:
      return std::stoi(std::get<std::string>(m_value));
  }

  throw std::runtime_error(
      std::format("Cannot convert {} to uint32_t", valueTypeString(getType())));
}

template <>
uint64_t Value::getValue<uint64_t>() {
  switch (getType()) {
    case ValueType::U8:
      return castValue<uint64_t, uint8_t>(m_value);
    case ValueType::U16:
      return castValue<uint64_t, uint16_t>(m_value);
    case ValueType::U32:
      return castValue<uint64_t, uint32_t>(m_value);
    case ValueType::U64:
      return std::get<uint64_t>(m_value);
    case ValueType::I8:
      return castValue<uint64_t, int8_t>(m_value);
    case ValueType::I16:
      return castValue<uint64_t, int16_t>(m_value);
    case ValueType::I32:
      return castValue<uint64_t, int32_t>(m_value);
    case ValueType::I64:
      return castValue<uint64_t, int64_t>(m_value);
    case ValueType::SGL:
      return castValue<uint64_t, float>(m_value);
    case ValueType::DBL:
      return castValue<uint64_t, double>(m_value);
    case ValueType::BOOL:
      return std::get<bool>(m_value) ? 1 : 0;
    case ValueType::STRING:
      return std::stoi(std::get<std::string>(m_value));
  }

  throw std::runtime_error(
      std::format("Cannot convert {} to uint64_t", valueTypeString(getType())));
}

template <>
int8_t Value::getValue<int8_t>() {
  switch (getType()) {
    case ValueType::U8:
      return castValue<int8_t, uint8_t>(m_value);
    case ValueType::U16:
      return castValue<int8_t, uint16_t>(m_value);
    case ValueType::U32:
      return castValue<int8_t, uint32_t>(m_value);
    case ValueType::U64:
      return castValue<int8_t, uint64_t>(m_value);
    case ValueType::I8:
      return std::get<int8_t>(m_value);
    case ValueType::I16:
      return castValue<int8_t, int16_t>(m_value);
    case ValueType::I32:
      return castValue<int8_t, int32_t>(m_value);
    case ValueType::I64:
      return castValue<int8_t, int64_t>(m_value);
    case ValueType::SGL:
      return castValue<int8_t, float>(m_value);
    case ValueType::DBL:
      return castValue<int8_t, double>(m_value);
    case ValueType::BOOL:
      return std::get<bool>(m_value) ? 1 : 0;
    case ValueType::STRING:
      return std::stoi(std::get<std::string>(m_value));
  }

  throw std::runtime_error(
      std::format("Cannot convert {} to int8_t", valueTypeString(getType())));
}

template <>
int16_t Value::getValue<int16_t>() {
  switch (getType()) {
    case ValueType::U8:
      return castValue<int16_t, uint8_t>(m_value);
    case ValueType::U16:
      return castValue<int16_t, uint16_t>(m_value);
    case ValueType::U32:
      return castValue<int16_t, uint32_t>(m_value);
    case ValueType::U64:
      return castValue<int16_t, uint64_t>(m_value);
    case ValueType::I8:
      return castValue<int16_t, int8_t>(m_value);
    case ValueType::I16:
      return std::get<int16_t>(m_value);
    case ValueType::I32:
      return castValue<int16_t, int32_t>(m_value);
    case ValueType::I64:
      return castValue<int16_t, int64_t>(m_value);
    case ValueType::SGL:
      return castValue<int16_t, float>(m_value);
    case ValueType::DBL:
      return castValue<int16_t, double>(m_value);
    case ValueType::BOOL:
      return std::get<bool>(m_value) ? 1 : 0;
    case ValueType::STRING:
      return std::stoi(std::get<std::string>(m_value));
  }

  throw std::runtime_error(
      std::format("Cannot convert {} to int16_t", valueTypeString(getType())));
}

template <>
int32_t Value::getValue<int32_t>() {
  switch (getType()) {
    case ValueType::U8:
      return castValue<int32_t, uint8_t>(m_value);
    case ValueType::U16:
      return castValue<int32_t, uint16_t>(m_value);
    case ValueType::U32:
      return castValue<int32_t, uint32_t>(m_value);
    case ValueType::U64:
      return castValue<int32_t, uint64_t>(m_value);
    case ValueType::I8:
      return castValue<int32_t, int8_t>(m_value);
    case ValueType::I16:
      return castValue<int32_t, int16_t>(m_value);
    case ValueType::I32:
      return std::get<int32_t>(m_value);
    case ValueType::I64:
      return castValue<int32_t, int64_t>(m_value);
    case ValueType::SGL:
      return castValue<int32_t, float>(m_value);
    case ValueType::DBL:
      return castValue<int32_t, double>(m_value);
    case ValueType::BOOL:
      return std::get<bool>(m_value) ? 1 : 0;
    case ValueType::STRING:
      return std::stoi(std::get<std::string>(m_value));
  }

  throw std::runtime_error(
      std::format("Cannot convert {} to int32_t", valueTypeString(getType())));
}

template <>
int64_t Value::getValue<int64_t>() {
  switch (getType()) {
    case ValueType::U8:
      return castValue<int64_t, uint8_t>(m_value);
    case ValueType::U16:
      return castValue<int64_t, uint16_t>(m_value);
    case ValueType::U32:
      return castValue<int64_t, uint32_t>(m_value);
    case ValueType::U64:
      return castValue<int64_t, uint64_t>(m_value);
    case ValueType::I8:
      return castValue<int64_t, int8_t>(m_value);
    case ValueType::I16:
      return castValue<int64_t, int16_t>(m_value);
    case ValueType::I32:
      return castValue<int64_t, int32_t>(m_value);
    case ValueType::I64:
      return std::get<int64_t>(m_value);
    case ValueType::SGL:
      return castValue<int64_t, float>(m_value);
    case ValueType::DBL:
      return castValue<int64_t, double>(m_value);
    case ValueType::BOOL:
      return std::get<bool>(m_value) ? 1 : 0;
    case ValueType::STRING:
      return std::stoi(std::get<std::string>(m_value));
  }

  throw std::runtime_error(
      std::format("Cannot convert {} to int64_t", valueTypeString(getType())));
}

template <>
float Value::getValue<float>() {
  switch (getType()) {
    case ValueType::U8:
      return castValue<float, uint8_t>(m_value);
    case ValueType::U16:
      return castValue<float, uint16_t>(m_value);
    case ValueType::U32:
      return castValue<float, uint32_t>(m_value);
    case ValueType::U64:
      return castValue<float, uint64_t>(m_value);
    case ValueType::I8:
      return castValue<float, int8_t>(m_value);
    case ValueType::I16:
      return castValue<float, int16_t>(m_value);
    case ValueType::I32:
      return castValue<float, int32_t>(m_value);
    case ValueType::I64:
      return castValue<float, int64_t>(m_value);
    case ValueType::SGL:
      return std::get<float>(m_value);
    case ValueType::DBL:
      return castValue<float, double>(m_value);
    case ValueType::BOOL:
      return std::get<bool>(m_value) ? 1.0f : 0.0f;
    case ValueType::STRING:
      return std::stof(std::get<std::string>(m_value));
  }

  throw std::runtime_error(
      std::format("Cannot convert {} to float", valueTypeString(getType())));
}

template <>
double Value::getValue<double>() {
  switch (getType()) {
    case ValueType::U8:
      return castValue<double, uint8_t>(m_value);
    case ValueType::U16:
      return castValue<double, uint16_t>(m_value);
    case ValueType::U32:
      return castValue<double, uint32_t>(m_value);
    case ValueType::U64:
      return castValue<double, uint64_t>(m_value);
    case ValueType::I8:
      return castValue<double, int8_t>(m_value);
    case ValueType::I16:
      return castValue<double, int16_t>(m_value);
    case ValueType::I32:
      return castValue<double, int32_t>(m_value);
    case ValueType::I64:
      return castValue<double, int64_t>(m_value);
    case ValueType::SGL:
      return castValue<double, float>(m_value);
    case ValueType::DBL:
      return std::get<double>(m_value);
    case ValueType::BOOL:
      return std::get<bool>(m_value) ? 1.0 : 0.0;
    case ValueType::STRING:
      return std::stod(std::get<std::string>(m_value));
  }

  throw std::runtime_error(
      std::format("Cannot convert {} to double", valueTypeString(getType())));
}

template <>
bool Value::getValue<bool>() {

  switch (getType()) {
    case ValueType::U8:
      return std::get<uint8_t>(m_value) != 0;
    case ValueType::U16:
      return std::get<uint16_t>(m_value) != 0;
    case ValueType::U32:
      return std::get<uint32_t>(m_value) != 0;
    case ValueType::U64:
      return std::get<uint64_t>(m_value) != 0;
    case ValueType::I8:
      return std::get<int8_t>(m_value) != 0;
    case ValueType::I16:
      return std::get<int16_t>(m_value) != 0;
    case ValueType::I32:
      return std::get<int32_t>(m_value) != 0;
    case ValueType::I64:
      return std::get<int64_t>(m_value) != 0;
    case ValueType::SGL:
      return std::get<float>(m_value) != 0;
    case ValueType::DBL:
      return std::get<double>(m_value) != 0;
    case ValueType::BOOL:
      return std::get<bool>(m_value);
    case ValueType::STRING:
      return Config::truthful.contains(std::get<std::string>(m_value));
  }

  throw std::runtime_error(
      std::format("Cannot convert {} to string", valueTypeString(getType())));
}

template <>
std::string Value::getValue<std::string>() {
  switch (getType()) {
    case ValueType::U8:
      return std::format("{}", std::get<uint8_t>(m_value));
    case ValueType::U16:
      return std::format("{}", std::get<uint16_t>(m_value));
    case ValueType::U32:
      return std::format("{}", std::get<uint32_t>(m_value));
    case ValueType::U64:
      return std::format("{}", std::get<uint64_t>(m_value));
    case ValueType::I8:
      return std::format("{}", std::get<int8_t>(m_value));
    case ValueType::I16:
      return std::format("{}", std::get<int16_t>(m_value));
    case ValueType::I32:
      return std::format("{}", std::get<int32_t>(m_value));
    case ValueType::I64:
      return std::format("{}", std::get<int64_t>(m_value));
    case ValueType::SGL:
      return std::format("{}", std::get<float>(m_value));
    case ValueType::DBL:
      return std::format("{}", std::get<double>(m_value));
    case ValueType::BOOL:
      return std::get<bool>(m_value) ? "T" : "F";
    case ValueType::STRING:
      return std::get<std::string>(m_value);
    case ValueType::PATH:
      return std::get<Path>(m_value).string();
  }

  throw std::runtime_error(
      std::format("Cannot convert {} to string", valueTypeString(getType())));
}

template <>
Path Value::getValue<Path>() {
  switch (getType()) {
    case ValueType::STRING:
      return std::get<std::string>(m_value);
    case ValueType::PATH:
      return std::get<Path>(m_value);
  }

  throw std::runtime_error(
      std::format("Cannot convert {} to Path", valueTypeString(getType())));
}

}  // namespace Config
