#ifndef GOLF_SCENE_H
#define GOLF_SCENE_H

#pragma once

#include <list>
#include <mutex>

#include "Window.h"

class Context;
class Camera;
class GameObject;

class Scene {
    friend void Window::on_update();
   public:
    Scene(float width, float height, Context *context);

    void addObject(GameObject *gameObject);

    void on_update();

    Context *getContext();

    void destroyGameObject(GameObject *gameObject);
   private:
    void destroyGameObjects();
   private:
    std::mutex m_gameObjects_mutex;
    std::list<GameObject *> m_gameObjects;
    std::queue<GameObject *> m_toDestroyObjects;

    Camera *m_pCamera;

    Context *m_pGameContext;
};

#endif  // GOLF_SCENE_H
