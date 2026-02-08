cmake_minimum_required(VERSION 3.28)

include(FetchContent)
FetchContent_Declare(TGUI
    GIT_REPOSITORY https://github.com/texus/TGUI.git
    GIT_TAG v1.12.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(TGUI)
