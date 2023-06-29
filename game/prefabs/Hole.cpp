#include "Hole.h"

#include <SFML/Graphics.hpp>

#include "../../headers/Log.h"


Hole::Hole() {
    auto texture = new sf::Texture();
    if(!texture->loadFromFile("../game/sprites/hole.png")){
        LOG_ERROR("Texture hole did not load!");
    }
    setTexture(texture);
}
