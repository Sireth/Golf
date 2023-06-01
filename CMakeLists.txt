cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(pong)

set(PONG_SOURCES src/main.cpp)
set(PONG_HEADERS )

add_executable(pong ${PONG_SOURCES} ${PONG_HEADERS})


# SFML
add_subdirectory(externals/SFML)
target_include_directories(pong PRIVATE externals/SFML)
target_link_libraries(pong PRIVATE sfml-audio sfml-graphics sfml-window sfml-system sfml-network)
