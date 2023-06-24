#ifndef PONG_RECTANGLE_H
#define PONG_RECTANGLE_H

#include "../../headers/GameObject.h"
#include "SFML/Graphics/Color.hpp"
#include "box2d/b2_body.h"
#include "glm/vec3.hpp"

class Rectangle:public GameObject {
   public:
    Rectangle(glm::vec3 position, glm::vec2 size, sf::Color color);

    glm::vec2 m_size;

    b2Body* m_body;
};

#endif  // PONG_RECTANGLE_H
