cmake_minimum_required(VERSION 3.28)

include(FetchContent)
FetchContent_Declare(fmtlog
    GIT_REPOSITORY https://github.com/MengRao/fmtlog.git
    GIT_TAG v2.3.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(fmtlog)

#the fmtlog repo is not setup to integrate into a higher level CMake config
# so some additional details need to be filled in.
target_include_directories(fmtlog-static
    PUBLIC
        ${fmtlog_SOURCE_DIR}
        ${fmtlog_SOURCE_DIR}/fmt/include
)

target_link_libraries(fmtlog-static
    PUBLIC
        fmt
)
