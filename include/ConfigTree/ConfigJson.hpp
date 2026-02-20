#ifndef ConfigJson_hpp_
#define ConfigJson_hpp_

#include <filesystem>

#include "Manager.hpp"

namespace Config {

/**
 * This class is currently static dispatch and wouldn't need to even be a class
 * but the plan is to eventually have polymorphism with other config formats
 * that can be loaded into the ConfigTree structure.
 */
class Json {
 public:
  Json(Path path) : m_path{path} {}
  ~Json() = default;

  void load(Manager& mgr);
  void save(const Manager& mgr);

  Path getPath() { return m_path; }

 private:
  Path m_path;
};
}  // namespace Config

#endif  // ConfigJson_hpp_
