#include "ConfigTree/ConfigJson.hpp"

#include <format>

#include "simdjson.h"

namespace Config {

using namespace simdjson;

void recurseJson(Manager& mgr, Element* parent, Hierarchy& hierarchy,
                 dom::element& jsonElem) {
  Element* el = nullptr;
  if (hierarchy.empty()) {
    el = mgr.createElement("", parent);
  } else {
    el = mgr.createElement(hierarchy.back(), parent);
  }

  int i{0};  // used for array indexing

  switch (jsonElem.type()) {
    case dom::element_type::ARRAY:
      el->setArrayType();

      for (dom::element child : dom::array(jsonElem)) {
        hierarchy.emplace_back(std::format("[{}]", i));
        recurseJson(mgr, el, hierarchy, child);
        hierarchy.pop_back();
        ++i;
      }
      break;

    case dom::element_type::BOOL:
      el->setValue(bool(jsonElem));
      break;

    case dom::element_type::DOUBLE:
      el->setValue(double(jsonElem));
      break;

    case dom::element_type::INT64:
      el->setValue(int64_t(jsonElem));
      break;

    case dom::element_type::NULL_VALUE:
      // leave element value as unset
      break;

    case dom::element_type::OBJECT:
      el->setObjectType();

      for (dom::key_value_pair field : dom::object(jsonElem)) {
        hierarchy.emplace_back(field.key);
        recurseJson(mgr, el, hierarchy, field.value);
        hierarchy.pop_back();
      }
      break;

    case dom::element_type::STRING:
      el->setValue(std::string_view(jsonElem));
      break;

    case dom::element_type::UINT64:
      el->setValue(uint64_t(jsonElem));
      break;
  }
}

void Json::load(Manager& mgr) {
  dom::parser parser;
  dom::element doc = parser.load(m_path.string());

  Hierarchy hierarchy{};

  recurseJson(mgr, nullptr, hierarchy, doc);
}
}  // namespace Config
