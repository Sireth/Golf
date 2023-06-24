#include "Hole.h"

#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RenderTexture.hpp"

Hole::Hole(glm::vec3 position) {

    sf::CircleShape circle(RADIUS);
    sf::RenderTexture texture;
    circle.setOrigin({0,0});
    circle.setFillColor(sf::Color::Black);
    texture.create({2 * RADIUS,2 * RADIUS});
    texture.clear();
    texture.clear(sf::Color::Transparent);
    texture.draw(circle);
    texture.display();
    setPosition(position);
    auto *nt = new sf::Texture(texture.getTexture());
    setTexture(nt);

}
