cmake_minimum_required(VERSION 3.28)

add_library(ConfigTree STATIC)

target_sources(ConfigTree
    PRIVATE
        ConfigJson.cpp
        Value.cpp
        Lookup.cpp
        Element.cpp
        Manager.cpp
)

target_compile_features(ConfigTree
    PRIVATE
        cxx_std_20
)

target_include_directories(ConfigTree
    PUBLIC
        ../../include
)
