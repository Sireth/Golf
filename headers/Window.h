#ifndef PONG_WINDOW_H
#define PONG_WINDOW_H

#pragma once
#include <glm/ext/matrix_float4x4.hpp>
#include <mutex>
#include <string>

#include "Context.h"

namespace sf {
    struct RenderWindow;
}

class GameObject;

class Scene;

class Window{
   public:
    Window(std::string title, unsigned int width, unsigned int height, Context &context);
    ~Window();

    Window(const Window&) = delete;
    Window(Window&&) = delete;
    Window& operator=(const Window&) = delete;
    Window& operator=(Window&&) = delete;

    void on_update();
    void on_updateScene();
    [[nodiscard]] unsigned int get_width() const { return m_data.width; }
    [[nodiscard]] unsigned int get_height() const { return m_data.height; }

    void setCurrentScene(Scene *scene);

    void shutdown();

   private:
    struct WindowData
    {
        std::string title;
        unsigned int width;
        unsigned int height;
    };

    int init();
    void renderObject(GameObject *gameObject);



    sf::RenderWindow* m_pWindow = nullptr;
    std::mutex m_pWindow_mutex;

    glm::mat4 m_viewMatrix{1};

    Scene *m_pCurrentScene;

    WindowData m_data;

    Context &m_gameContext;
};

#endif  // PONG_WINDOW_H
