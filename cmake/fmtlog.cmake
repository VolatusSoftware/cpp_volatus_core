cmake_minimum_required(VERSION 3.28)

include(FetchContent)
FetchContent_Declare(fmtlog
    GIT_REPOSITORY https://github.com/MengRao/fmtlog.git
    GIT_TAG v2.3.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(fmtlog)
