#ifndef GOLF_BUTTON_H
#define GOLF_BUTTON_H
#pragma once

#include "../GameObject.h"
#include "SFML/Graphics.hpp"

class Button: public GameObject {

    enum Mouse{
        Click,
        Down,
        Up,
        Over,
        Out,
        
        CountActions
    };
    
    std::unique_ptr<sf::Text> m_pText;
    sf::Font m_font;

    glm::vec2 m_size;

    sf::Color m_backgroundColor;

    std::vector<std::function<void()>> m_actionFunctions{CountActions, []{return ;}};
    bool m_actions[CountActions]{};

    void updateTextureBackground();
    void updateTextureBackground(sf::Texture *texture);

   public:
    explicit Button(glm::vec2 size = glm::vec2(10), sf::Color color = sf::Color::White);
    explicit Button(sf::Text text, glm::vec2 size = glm::vec2(10), sf::Color color = sf::Color::White);


    void setText(sf::Text text);
    void setText(const std::string& string);
    void setFont(sf::Font font);
    void setCharacterSize(unsigned int size);
    void setTextColor(sf::Color color);

   
    void setMouseClickAction(std::function<void()> action);
    void setMouseDownAction(std::function<void()> action);
    void setMouseUpAction(std::function<void()> action);
    void setMouseOverAction(std::function<void()> action);
    void setMouseOutAction(std::function<void()> action);


    void setSize(glm::vec2 size);


    void setBackgroundColor(sf::Color color);
    void setBackground(const sf::Texture& texture);


    glm::vec2 getSize() {return m_size;};

    void update() override;

   private:
    void checkMouseActions();
    void startMouseFunctions();

};

#endif  // GOLF_BUTTON_H
