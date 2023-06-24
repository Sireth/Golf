#include "Ball.h"

#include "../../headers/GameObject.h"
#include "../../headers/Log.h"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RenderTexture.hpp"
#include "glm/gtx/compatibility.hpp"

#define SCALE 30

Ball::Ball(char number, glm::vec3 position): number(number) {

    LOG_INFO("Player created");
    sf::CircleShape circle(RADIUS);
    sf::RenderTexture texture;


    texture.create({2 * RADIUS,2 * RADIUS});
    texture.setSmooth(true);
    texture.clear(sf::Color::Transparent);

    circle.setFillColor(sf::Color::White);

    texture.draw(circle);

    circle.setFillColor(colors[number]);
    circle.setRadius(RADIUS-3);
    circle.setOrigin({-3,-3});

    texture.draw(circle);
    texture.display();
    setPosition(position);
    auto *nt = new sf::Texture(texture.getTexture());
    setTexture(nt);
}
void Ball::fixedUpdate() {
    GameObject::fixedUpdate();
    auto pos = m_body->GetPosition();
    setPosition({pos.x*SCALE,pos.y*SCALE, getPosition().z});
}
