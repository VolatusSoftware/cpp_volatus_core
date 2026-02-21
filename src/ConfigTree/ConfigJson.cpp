#include "ConfigTree/ConfigJson.hpp"

#include <format>

#include "simdjson.h"

namespace Config {

using namespace simdjson;

void recurseJson(Manager& mgr, Element* parent, Hierarchy& hierarchy,
                 dom::element& jsonElem, bool nestedMeta = false) {
  Element* el = nullptr;

  // Check if we need to handle the two special name cases. "Meta" and "Value"
  // are the only two reserved names in this format.
  bool isMeta =
      nestedMeta || (!hierarchy.empty() && hierarchy.back() == "Meta");

  bool isValue = !hierarchy.empty() && hierarchy.back() == "Value";

  // only create a new element if not Meta nested element.
  // Meta values will be set on parent input instead of on a new element.
  if (isMeta || isValue) {
    // set el to the meta object's parent since that is the element the meta
    // values will be applied to.

    // also when name is "Value" the value gets applied to the parent element
    // passed in. This is the long form name when an element has both a value
    // and Meta fields present.

    el = parent;
  } else {
    if (!hierarchy.empty()) {
      el = mgr.createElement(hierarchy.back(), parent);
    }

    // el will remain nullptr when processing the root object element.
  }

  int i{0};  // used for array indexing

  switch (jsonElem.type()) {
    case dom::element_type::ARRAY:
      if (nestedMeta) {
        throw std::invalid_argument("Arrays as Meta values are not supported.");
      }

      el->setArrayType();

      for (dom::element child : dom::array(jsonElem)) {
        hierarchy.emplace_back(std::format("[{}]", i));
        recurseJson(mgr, el, hierarchy, child);
        hierarchy.pop_back();
        ++i;
      }
      break;

    case dom::element_type::BOOL:
      if (isMeta) {
        el->setMetaValue(hierarchy.back(), bool(jsonElem));
      } else {
        el->setValue(bool(jsonElem));
      }
      break;

    case dom::element_type::DOUBLE:
      if (isMeta) {
        el->setMetaValue(hierarchy.back(), double(jsonElem));
      } else {
        el->setValue(double(jsonElem));
      }
      break;

    case dom::element_type::INT64:
      if (isMeta) {
        el->setMetaValue(hierarchy.back(), int64_t(jsonElem));
      } else {
        el->setValue(int64_t(jsonElem));
      }
      break;

    case dom::element_type::NULL_VALUE:
      // leave element value as unset
      break;

    case dom::element_type::OBJECT:
      if (nestedMeta) {
        throw std::invalid_argument(
            "Objects as Meta values are not supported.");
      }

      for (dom::key_value_pair field : dom::object(jsonElem)) {
        hierarchy.emplace_back(field.key);
        recurseJson(mgr, el, hierarchy, field.value, isMeta);
        hierarchy.pop_back();
      }
      break;

    case dom::element_type::STRING:
      if (isMeta) {
        el->setMetaValue(hierarchy.back(), std::string_view(jsonElem));
      } else {
        el->setValue(std::string_view(jsonElem));
      }
      break;

    case dom::element_type::UINT64:
      if (isMeta) {
        el->setMetaValue(hierarchy.back(), uint64_t(jsonElem));
      } else {
        el->setValue(uint64_t(jsonElem));
      }
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
