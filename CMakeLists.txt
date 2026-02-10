cmake_minimum_required(VERSION 3.28)

#Up front are a handful of project definitions to prevent needing to dig for the
# commands that set these values. Update this to match your project name.

set(IG_PROJECT_NAME volatus_core)
set(IG_PROJECT_VERSION 0.1.0)

#Setting a variable to tell TexusGUI library to use basic SFML Graphics features
# for its backend drawing capabilities. May change this to OpenGL in the future
# (SFML uses OpenGL under the hood already) if I need to get fancier with GUIs.
set(TGUI_BACKEND SFML_GRAPHICS)

#SFML is the primary library for graphical drawing, windowing, input, and audio
# to enable all the core capabilities of Volatus in C++.
# Volatus also uses its TCP and UDP functionality for requests/commands and
# telemetry respectively.
include(cmake/sfml.cmake)

#TexusGUI is a widgets library that can run on top of SFML to provide common
# GUI components such as buttons, nested windows, treeviews, labels, etc.
# for the less artistic graphical components in the GUIs.
# Volatus extends the widget hierarchy to implement its specific GUI controls.
include(cmake/tgui.cmake)

#Google's Protobuf provides the serialization format used in TCP and UDP
# communication. This makes it easier to interact with Volatus from other
# development environments. The volatus_proto submodule provides Volatus'
# specific message definition .proto files.
include(cmake/protobuf.cmake)

include(cmake/fmtlog.cmake)

#Define the CMake project and version as configured at the top of this file.
# C and C++ are used as the implementation languages.
project(${IG_PROJECT_NAME} VERSION ${IG_PROJECT_VERSION} LANGUAGES C CXX)

#Builds Volatus' specific Protobuf messages.
add_subdirectory(volatus_proto)

#Houses the builds for Volatus libraries and executables.
add_subdirectory(src)
