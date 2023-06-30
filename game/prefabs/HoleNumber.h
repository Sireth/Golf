#ifndef GOLF_HOLENUMBER_H
#define GOLF_HOLENUMBER_H
#pragma once

#include "../../headers/templates/Text.h"


class HoleNumber : public GameObject{
   public:
    uint m_number = 1;
    std::unique_ptr<sf::Font> m_pFont;
    std::unique_ptr<sf::Text> m_pText;

    void update() override;
};

#endif  // GOLF_HOLENUMBER_H
