#ifndef PONG_GAMEOBJECT_H
#define PONG_GAMEOBJECT_H

#pragma once

#include "Component.h"

#include <list>
#include <mutex>

#include "glm/glm.hpp"


namespace sf {
struct Texture;
}


class GameObject {
   protected:
    glm::mat4 m_transform{1};
    glm::vec3 m_position{0};
    glm::vec3 m_rotation{0};
    glm::vec3 m_scale{1};

    std::mutex m_transform_mutex;

    sf::Texture *m_texture;
    std::mutex m_texture_mutex;

    std::list<Component *> components;

   public:
    void lockTextureMutex() {m_texture_mutex.lock();};
    sf::Texture *getTexture();
    void unlockTextureMutex() {m_texture_mutex.unlock();};
    void setTexture(sf::Texture *texture);
    void setTexture(std::string filename);

    void setPosition(glm::vec3 position);
    void setRotation(glm::vec3 rotation);
    void setScale(glm::vec3 scale);

    glm::vec3 getPosition();
    glm::vec3 getRotation();
    glm::vec3 getScale();



    glm::mat4 getTransform();
    void setTransform(glm::mat4 transform);
    void start();
    void update();
    void fixedUpdate();
};

#endif  // PONG_GAMEOBJECT_H
