#include "../headers/Scene.h"

#include <algorithm>
#include <SFML/Graphics.hpp>

#include "../headers/Camera.h"
#include "../headers/Context.h"

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
}
void Scene::destroyGameObject(GameObject *gameObject) {
    std::unique_lock<std::mutex> lock(m_gameObjects_mutex);
    auto searched =
        std::find(m_gameObjects.begin(), m_gameObjects.end(), gameObject);
    if (*searched) {
        m_gameObjects.erase(searched);
    }
    delete gameObject;
}
Context *Scene::getContext() { return m_pGameContext; }
