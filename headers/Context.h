#ifndef GOLF_CONTEXT_H
#define GOLF_CONTEXT_H

#pragma once
#include <chrono>
#include <glm/glm.hpp>
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Game.h"
#include "Window.h"
#include "Scene.h"

class Camera;

class Context {

    friend void Game::start();
    friend class Window;
    friend Scene::Scene(float width, float height, Context *context);

   private:
    struct WindowData
    {
        std::string title;
        unsigned width{};
        unsigned height{};
    };

    Camera *m_pCamera{};

    Game *m_pGame{};

    WindowData m_mainWidowData;
    Window *m_pWindow{};

    long deltaTime{};

    sf::Event m_event{};

    bool m_running = false;

    bool m_pressedKeys[static_cast<unsigned long>(sf::Keyboard::Key::KeyCount)]{};

    bool m_pressedMouseKeys [sf::Mouse::Button::ButtonCount]{};

    glm::vec2 m_mousePosition{};


    void updateMousePosition(glm::vec2 mousePosition);
    void setMouseKeyPressed(sf::Mouse::Button keyCode);
    void setMouseKeyReleased(sf::Mouse::Button keyCode);

    void setKeyPressed(sf::Keyboard::Key keyCode);
    void setKeyReleased(sf::Keyboard::Key keyCode);

    void setCamera(Camera *camera);

   public:

    Context();


    [[nodiscard]] bool getRunning() const{return m_running;};
    WindowData getWindowData(){return m_mainWidowData;};
    sf::Event &getEvent() {return m_event;};
    glm::vec2 getMousePosition();

    void setWindowData(WindowData win_data, Window *window);
    void setGame(Game *game);
    Game *getGame();
    Window *getWindow();


    bool isKeyPressed(sf::Keyboard::Key keyCode);
    [[maybe_unused]] bool isMouseKeyPressed(sf::Mouse::Button keyCode);


    glm::vec3 screenToWorldPoint(glm::vec2 pos);


    void stopGame();
};

#endif  // GOLF_CONTEXT_H
