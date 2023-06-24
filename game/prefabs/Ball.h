#ifndef PONG_BALL_H
#define PONG_BALL_H

#include "../../headers/GameObject.h"
#include "SFML/Graphics/Color.hpp"
#include "box2d/b2_body.h"
#include "SFML/Graphics/RenderTexture.hpp"

class Ball: public GameObject{
   public:
    enum {
        RADIUS = 15,
    };
    Ball(char number, glm::vec3 position);

    void fixedUpdate() override;

    char number;

    sf::Color colors[16] = {sf::Color::White, sf::Color::Yellow, sf::Color::Blue,
                            sf::Color::Red, {255, 0, 183}, {255, 153, 0},
                            sf::Color::Yellow, {87, 53, 2}, sf::Color::Black,
                        sf::Color::Green, sf::Color::Blue, sf::Color::Red,
                            {255, 0, 183}, {255, 153, 0}, sf::Color::Green, {87, 53, 2}};

    b2Body* m_body;
};

#endif  // PONG_BALL_H
