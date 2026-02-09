# cpp_volatus_core


## Prerequisites
- CMake
- Windows Builds
  - MinGW64 (MSYS2 recommended)
  - Windows SDK

This template was created on Windows and expects to use the MinGW64 toolchain (via MSYS2 on my system). The ultimate goal is for this project to be cross-platform to at least the following platforms:
- Windows
- Linux (Not tested yet)
- [NI Linux Real-Time](#wait-ni-linux-real-time) (Not tested yet)

CMake is used as the build configuration tooling and presets will be available for the supported platform and toolchains.

## Using the Template
To use the template, you can create a new repository in GitHub from this template. You'll then need to customize the project and executable/library names in the `CMakeLists.txt` files.

### Changing the SFML/TGUI Version

The template has `/cmake/SFML.cmake` and `/cmake/TGUI.cmake` which provide the functionality for automatically cloning the respective repositories and integrating their build outputs. The `FetchContent` calls in these CMake scripts includes a tag name to point to specific releases. This tag can be changed to a different tag or commit hash to use different versions of those libraries.

### Using Different Toolchains

The expected place to configure different toolchains is in `CMakePresets.json`. While beyond the scope of this readme, there are numerous (albeit often confusing or out of date) resources available online for what different configurations would look like. As support for this template repository grows there will be a handful of different examples in the template's CMakePresets.json file but they will typically be catered to GNU toolchains.

## Wait? NI Linux Real-Time?
Yes, this will also serve as the basis for creating console/headless applications without the graphical components. The initial consumer of this template and build configuration will be a data acquisition and control software stack called Volatus. The goal is to have everything but the GUI functionality built to run on CompactRIO and PXI platforms that run on the NILRT operating system.

The networking functionality for those tools will be built using SFML's networking library to be able to re-use the communication components across the various tools.
