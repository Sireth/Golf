#ifndef GOLF_WINDOW_H
#define GOLF_WINDOW_H

#pragma once
#include <glm/ext/matrix_float4x4.hpp>
#include <mutex>
#include <string>

#include "Game.h"

namespace sf {
    struct RenderWindow;
}

class GameObject;
class Scene;
class Context;

class Window{

    friend void Game::on_eventsUpdate();

   public:
    Window(std::string title, unsigned int width, unsigned int height, Context *context);
    ~Window();

    Window(const Window&) = delete;
    Window(Window&&) = delete;
    Window& operator=(const Window&) = delete;
    Window& operator=(Window&&) = delete;

    void on_update();
    void on_updateScene();
    [[maybe_unused]] [[nodiscard]] unsigned int get_width() const;
    [[maybe_unused]] [[nodiscard]] unsigned int get_height() const;

    void setCurrentScene(Scene *scene);

    void shutdown();

   private:

    int init();

    void renderObject(GameObject *gameObject);

    void on_updateEvents();


    sf::RenderWindow* m_pWindow = nullptr;
    std::mutex m_pWindow_mutex;

    glm::mat4 m_viewMatrix{1};

    Scene *m_pCurrentScene;

    Context *m_pGameContext;
};

#endif  // GOLF_WINDOW_H
