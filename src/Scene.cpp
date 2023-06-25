#include "../headers/Scene.h"

#include <SFML/Graphics.hpp>
#include <algorithm>

#include "../game/scripts/ExitGameScript.h"
#include "../headers/Camera.h"
#include "../headers/Context.h"
#include "../headers/Log.h"
#include "../headers/templates/Button.h"

bool sortGM(GameObject *f, GameObject *s) {
    return f->getPosition().z < s->getPosition().z;
}

void Scene::addObject(GameObject *gameObject) {
    {
        std::unique_lock<std::mutex> lock(m_gameObjects_mutex);
        m_gameObjects.push_back(gameObject);
        m_gameObjects.sort(sortGM);
    }
    gameObject->m_pScene = this;
    gameObject->start();
}
GameObject::~GameObject() { delete m_texture; }

Scene::Scene(float width, float height, Context *context)
    : m_pGameContext(context) {
    m_pCamera = new Camera(width, height);
    context->setCamera(m_pCamera);
    addObject(m_pCamera);
}
void Scene::on_update() {
    std::unique_lock<std::mutex> lock(m_gameObjects_mutex);
    std::for_each(m_gameObjects.begin(), m_gameObjects.end(),
                  [](GameObject *gameObject) { gameObject->fixedUpdate(); });
    destroyGameObjects();
}
void Scene::destroyGameObject(GameObject *gameObject) {
    if(gameObject){
        m_toDestroyObjects.push(gameObject);
    }
}
void Scene::destroyGameObjects() {
    while (!m_toDestroyObjects.empty()){
        auto gameObject = m_toDestroyObjects.front();
        auto searched =
            std::find(m_gameObjects.begin(), m_gameObjects.end(), gameObject);
        m_toDestroyObjects.pop();
        if (*searched) {
            m_gameObjects.erase(searched);
        }
        delete gameObject;
    }
}
Context *Scene::getContext() {
    return m_pGameContext;
}

