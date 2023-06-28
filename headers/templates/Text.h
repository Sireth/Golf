#ifndef GOLF_TEXT_H
#define GOLF_TEXT_H
#pragma once

#include <SFML/Graphics.hpp>

#include "../GameObject.h"


class Text: public GameObject{

    std::unique_ptr<sf::Text> m_pText;

   public:
    Text();
    explicit Text(const sf::Text& text);
    explicit Text(const std::string& string, unsigned characterSize = 30);

    void setText(const sf::Text& text);
    void setText(const std::string& string);
    void setColor(sf::Color color);
    void setFont(const sf::Font& font);
    void setCharacterSize(unsigned size);


    protected:
     void updateTextTexture();
};

#endif  // GOLF_TEXT_H
