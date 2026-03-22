cmake_minimum_required(VERSION 3.28)

add_library(VolatusModule STATIC)

target_sources(VolatusModule
    PRIVATE
        Module.cpp
)

target_include_directories(VolatusModule
    PUBLIC
        ../../include
)
