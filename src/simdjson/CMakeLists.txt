cmake_minimum_required(VERSION 3.28)

add_library(simdjson STATIC)

target_sources(simdjson
    PRIVATE
        simdjson.cpp
)

target_include_directories(simdjson
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
