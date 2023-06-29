cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(golf)

set(ENGINE_SOURCES
        src/main.cpp
        src/Window.cpp
        src/utils.cpp
        src/Scene.cpp
        src/Camera.cpp
        src/Game.cpp
        src/GameObject.cpp
        src/Context.cpp
        src/templates/Button.cpp
        src/templates/Text.cpp)

set(ENGINE_HEADERS
        headers/Window.h
        headers/Log.h
        headers/Game.h
        headers/GameObject.h
        headers/Component.h
        headers/Scene.h
        headers/utils.h
        headers/Camera.h
        headers/Context.h
        headers/templates/Button.h
        headers/templates/Text.h)

set(GAME_SOURCES
        game/scenes/Menu.cpp
        game/scripts/ExitGameScript.cpp
        game/Golf.cpp
        game/prefabs/Field.cpp
        game/prefabs/Wall.cpp)

set(GAME_HEADERS
        game/scenes/Menu.h
        game/scripts/ExitGameScript.h
        game/Golf.h
        game/prefabs/Field.h
        game/prefabs/Wall.h game/prefabs/Ball.cpp game/prefabs/Ball.h game/prefabs/Hole.cpp game/prefabs/Hole.h game/scripts/TextInput.cpp game/scripts/TextInput.h game/scenes/GameScene.cpp game/scenes/GameScene.h)

add_executable(golf ${ENGINE_SOURCES} ${ENGINE_HEADERS} ${GAME_SOURCES} ${GAME_HEADERS})


# SFML
add_subdirectory(externals/SFML)
target_include_directories(golf PRIVATE externals/SFML)
target_link_libraries(golf PRIVATE sfml-audio sfml-graphics sfml-window sfml-system sfml-network)

# glm
add_subdirectory(externals/glm)
target_include_directories(golf PRIVATE externals/glm)
target_link_libraries(golf PRIVATE glm::glm)

# spdlog
add_subdirectory(externals/spdlog)
target_include_directories(golf PRIVATE externals/spdlog)
target_link_libraries(golf PRIVATE spdlog::spdlog)

# thread_pool
add_library(thread_pool externals/thread_pool/include/BS_thread_pool.hpp externals/thread_pool/include/BS_thread_pool.hpp)
set_target_properties(thread_pool PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(golf PRIVATE externals/thread_pool)
target_link_libraries(golf PRIVATE thread_pool)

#box_2d_lite
add_subdirectory(externals/box_2d)
target_include_directories(golf PRIVATE externals/box_2d)
target_link_libraries(golf PRIVATE box2d)

#json
add_subdirectory(externals/json)
target_include_directories(golf PRIVATE externals/json)
target_link_libraries(golf PRIVATE nlohmann_json::nlohmann_json)
