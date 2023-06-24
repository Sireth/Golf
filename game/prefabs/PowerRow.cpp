#include "PowerRow.h"

#include "../../headers/Log.h"

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderTexture.hpp"

PowerRow::PowerRow() {

    LOG_INFO("PowerRow");
    sf::RectangleShape rectangle(sf::Vector2f(m_size.x, m_size.y));
    sf::RenderTexture texture;
    rectangle.setFillColor(sf::Color::White);
    texture.create({static_cast<unsigned >(m_size.x), static_cast<unsigned >(m_size.y)});
    texture.clear();
    texture.draw(rectangle);
    texture.display();
    auto *nt = new sf::Texture(texture.getTexture());
    setTexture(nt);
    setPosition({0,0,0});
}
