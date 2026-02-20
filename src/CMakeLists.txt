cmake_minimum_required(VERSION 3.28)

add_subdirectory(simdjson)
#add_subdirectory(fmtlog)

add_subdirectory(ConfigTree)

add_executable(example)

target_sources(example
    PRIVATE
        example.cpp
)

#MinGW doesn't set the windows version properly, set it to Win10+
target_compile_definitions(example
    PRIVATE
        _WIN32_WINNT=0x0A00
)

target_compile_features(example
    PRIVATE
        cxx_std_20
)

target_include_directories(example
    PRIVATE
        ../include
)

target_link_libraries(example
    PRIVATE
        SFML::Graphics
        SFML::Audio
        SFML::Network
        TGUI::TGUI
        volatus_proto
        simdjson
        fmtlog-static
        ConfigTree
)

