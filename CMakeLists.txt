cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(pong)

set(PONG_SOURCES
        src/main.cpp
        src/Window.cpp
        src/utils.cpp
        src/Scene.cpp
        src/Component.cpp
        src/Camera.cpp
        src/Game.cpp
        src/GameObject.cpp
        src/Context.cpp)
set(PONG_HEADERS
        headers/Window.h
        headers/Log.h
        headers/Game.h
        headers/GameObject.h
        headers/Component.h
        headers/Scene.h
        headers/utils.h
        headers/Camera.h
        headers/Context.h)

add_executable(pong ${PONG_SOURCES} ${PONG_HEADERS})


# SFML
add_subdirectory(externals/SFML)
target_include_directories(pong PRIVATE externals/SFML)
target_link_libraries(pong PRIVATE sfml-audio sfml-graphics sfml-window sfml-system sfml-network)

# glm
add_subdirectory(externals/glm)
target_include_directories(pong PRIVATE externals/glm)
target_link_libraries(pong PRIVATE glm::glm)

# spdlog
add_subdirectory(externals/spdlog)
target_include_directories(pong PRIVATE externals/spdlog)
target_link_libraries(pong PRIVATE spdlog::spdlog)

# thread_pool
add_subdirectory(externals/thread_pool)
target_include_directories(pong PRIVATE externals/thread_pool)
target_link_libraries(pong PRIVATE thread_pool)