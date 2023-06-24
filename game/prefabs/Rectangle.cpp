#include "Rectangle.h"

#include "../../headers/Log.h"
#include "../../headers/GameObject.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics.hpp"

Rectangle::Rectangle(glm::vec3 position, glm::vec2 size, sf::Color color): m_size(size) {

    LOG_INFO("Rectangle created");
    sf::RectangleShape rectangle(sf::Vector2f(size.x, size.y));
    sf::RenderTexture texture;
    rectangle.setFillColor(color);
    setPosition(position);
    texture.create({static_cast<unsigned>(size.x), static_cast<unsigned>(size.y)});
    texture.clear();
    texture.draw(rectangle);
    texture.display();
    auto *nt = new sf::Texture(texture.getTexture());
    setTexture(nt);
}
