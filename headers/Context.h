#ifndef PONG_CONTEXT_H
#define PONG_CONTEXT_H

#pragma once
#include <glm/glm.hpp>
#include <string>

#include "SFML/Window/Event.hpp"

class Context {
   private:
    struct WindowData
    {
        std::string title;
        unsigned int width{};
        unsigned int height{};
    };

    WindowData m_mainWidowData;
    bool m_running = false;

    sf::Event m_event{};

   public:

    Context(){};

    WindowData getWindowData(){return m_mainWidowData;};

    void setWindowsData(WindowData win_data);

    [[nodiscard]] bool getRunning() const{return m_running;};

    sf::Event getEvent() {return m_event;};

};

#endif  // PONG_CONTEXT_H
