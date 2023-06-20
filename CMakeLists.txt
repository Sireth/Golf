cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(pong)

set(PONG_SOURCES src/main.cpp src/Window.cpp src/Game.cpp src/GameObject.cpp headers/GameObject.h headers/Component.h src/Scene.cpp headers/Scene.h src/utils.cpp headers/utils.h src/Camera.cpp headers/Camera.h src/Context.cpp headers/Context.h)
set(PONG_HEADERS headers/Window.h headers/Log.h headers/Game.h src/GameObject.cpp headers/GameObject.h headers/Component.h src/Scene.cpp headers/Scene.h src/Camera.cpp headers/Camera.h src/Context.cpp headers/Context.h)

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