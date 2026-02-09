cmake_minimum_required(VERSION 3.28)

set(IG_PROJECT_NAME volatus_core)
set(IG_PROJECT_VERSION 0.1.0)

set(TGUI_BACKEND SFML_GRAPHICS)

include(cmake/sfml.cmake)
include(cmake/tgui.cmake)
include(cmake/protobuf.cmake)

project(${IG_PROJECT_NAME} VERSION ${IG_PROJECT_VERSION} LANGUAGES C CXX)

add_subdirectory(volatus_proto)
add_subdirectory(src)
