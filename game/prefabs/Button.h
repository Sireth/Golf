#ifndef GOLF_BUTTON_H
#define GOLF_BUTTON_H
#pragma once

#include "../../headers/GameObject.h"
#include "SFML/Graphics.hpp"

class Button: public GameObject {

    Button(glm::vec2 size = glm::vec2(10), sf::Color color = sf::Color::Black, std::function<void()> action = [](){return ;});

    Button(sf::Text text, glm::vec2 size = glm::vec2(10), sf::Color color = sf::Color::Black, std::function<void()> action = [](){return ;});
    sf::Text m_text;
    sf::Font m_font;

    glm::vec2 m_size;

    sf::Color m_backgroundColor;
    bool m_pressed{};
    std::function<void()> m_action;

    sf::Texture createTexture();

   public:
    void setText(sf::Text text);
    void setText(const std::string& string);
    void setFont(sf::Font font);

    void setAction(std::function<void()> action);

    void setSize(glm::vec2 size);

    void setBackgroundColor(sf::Color color);


    glm::vec2 getSize() {return m_size;};


    bool isPressed() const {return m_pressed;};

};

#endif  // GOLF_BUTTON_H
