#ifndef VolatusConfigElement_hpp_
#define VolatusConfigElement_hpp_

#include "ConfigTree/Element.hpp"

namespace Volatus {
class ConfigElement {
 public:
  ConfigElement(Config::Element elem);

  std::string_view getName() { return m_element->getName(); }

 protected:
  Config::Element* get() { return m_element; }

 private:
  // Non-owning pointer to element represented by this Volatus Config Element
  // Config::Element instances are owned by a Config::Manager
  Config::Element* m_element = nullptr;
};
}  // namespace Volatus
#endif
