cmake_minimum_required(VERSION 3.28)

add_library(VolatusConfig STATIC)

target_sources(VolatusConfig
    PRIVATE
        ConfigTypes.cpp
        VolatusConfig.cpp
        SystemConfig.cpp
        ClusterConfig.cpp
        NodeConfig.cpp
        TaskConfig.cpp
        GroupConfig.cpp
        ChannelConfig.cpp
        ScalingConfig.cpp
)

target_compile_features(VolatusConfig
    PRIVATE
        cxx_std_20
)

target_include_directories(VolatusConfig
    PUBLIC
        ../../include
)
