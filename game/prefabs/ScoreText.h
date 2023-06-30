#ifndef GOLF_SCORETEXT_H
#define GOLF_SCORETEXT_H

#pragma once

#include "SFML/Graphics.hpp"

#include "../../headers/GameObject.h"
class ScoreText: public GameObject {
   public:
    int m_score;
    std::unique_ptr<sf::Font> m_pFont;
    std::unique_ptr<sf::Text> m_pText;

    void update() override;
};

#endif  // GOLF_SCORETEXT_H
