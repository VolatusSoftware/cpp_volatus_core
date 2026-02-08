cmake_minimum_required(VERSION 3.28)

set(IG_PROJECT_NAME SFML_TGUI)
set(IG_PROJECT_VERSION 0.1.0)

include(cmake/sfml.cmake)

set(TGUI_BACKEND SFML_GRAPHICS)
include(cmake/tgui.cmake)

include(cmake/protobuf.cmake)

project(${IG_PROJECT_NAME} VERSION ${IG_PROJECT_VERSION} LANGUAGES CXX)

add_subdirectory(src)
