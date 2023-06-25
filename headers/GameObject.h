#ifndef GOLF_GAMEOBJECT_H
#define GOLF_GAMEOBJECT_H

#pragma once

#include <list>
#include <mutex>
#include <glm/glm.hpp>

#include "Scene.h"

class Context;
class Component;

namespace sf {
struct Texture;
}


class GameObject {

    friend void Scene::addObject(GameObject *gameObject);

   protected:
    glm::mat4 m_transform{1};
    glm::vec3 m_position{0};
    glm::vec3 m_rotation{0};
    glm::vec3 m_scale{1};

    std::mutex m_transform_mutex;

    sf::Texture *m_texture= nullptr;
    std::mutex m_texture_mutex;

    std::mutex m_components_mutex;
    std::list<Component *> m_components;

   public:

    bool active = true;

    Scene *m_pScene = nullptr;


    ~GameObject();

    Context *getContext() const;

    void addComponent(Component *component);

    void destroy();


    void lockTextureMutex() {m_texture_mutex.lock();};
    sf::Texture *getTexture();
    void unlockTextureMutex() {m_texture_mutex.unlock();};
    void setTexture(sf::Texture *texture);
    [[maybe_unused]] void setTexture(std::string filename);

    void setPosition(glm::vec3 position);
    [[maybe_unused]] void setRotation(glm::vec3 rotation);
    [[maybe_unused]] void setScale(glm::vec3 scale);

    glm::vec3 getPosition();
    [[maybe_unused]] glm::vec3 getRotation();
    [[maybe_unused]] glm::vec3 getScale();



    glm::mat4 getTransform();
    [[maybe_unused]] void setTransform(glm::mat4 transform);
    virtual void start();
    virtual void update();
    virtual void fixedUpdate();
};

#endif  // GOLF_GAMEOBJECT_H
