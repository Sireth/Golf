#include "Wall.h"

#include <SFML/Graphics.hpp>

#include "../../headers/Log.h"

Wall::Wall(unsigned char group, unsigned char number)
    : m_group(group), m_number(number) {
    loadWallTexture();
}
void Wall::loadWallTexture() {
    std::string filename = "../game/sprites/wall_";
    filename += std::to_string(m_group);
    filename += "/Sprite " + std::to_string(m_number) + ".png";
    auto *texture = new sf::Texture();
    if (texture->loadFromFile(filename)) {
        setTexture(texture);
    } else {
        LOG_CRITICAL("Wrong group or number!");
    }
}
void Wall::setLocalPosition(glm::vec2 pos, GameObject *field) {
    auto fieldSize_u = field->getTexture()->getSize();
    auto wallSize_u = getTexture()->getSize();


    glm::vec2 wallSize;
    if(wallSize_u.x <64){
        wallSize = {32,32};
    }
    else{
        wallSize = {64,64};
    }

    glm::vec2 fieldSize(static_cast<float>(fieldSize_u.x), static_cast<float>(fieldSize_u.y));

    glm::vec3 newPos =
        glm::vec3(pos, 1) * glm::vec3(wallSize.x, -wallSize.y, 1) +
        glm::vec3(wallSize.x / 2, -wallSize.y / 2, 0) + field->getPosition()
        + glm::vec3(-fieldSize.x/2, fieldSize.y/2,0.1f);
    setPosition(newPos);
}
