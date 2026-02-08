cmake_minimum_required(VERSION 3.28)

add_executable(example)

target_sources(example
    PRIVATE
        example.cpp
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
        protobuf::libprotobuf
)

