#include "../headers/Scene.h"

#include <algorithm>

#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RenderTexture.hpp"

std::list<GameObject *>::iterator Scene::getGameObjectBeginIterator() {
    std::unique_lock<std::mutex> lock(m_gameObjects_mutex);
    return m_gameObjects.begin();
}
std::list<GameObject *>::iterator Scene::getGameObjectEndIterator() {
    std::unique_lock<std::mutex> lock(m_gameObjects_mutex);
    return m_gameObjects.end();
}
void Scene::addObject(GameObject *gameObject) {
    std::unique_lock<std::mutex> lock(m_gameObjects_mutex);
    m_gameObjects.push_back(gameObject);
    gameObject->start();
}
Scene::Scene(float width, float height, Context &context)
    : m_gameContext(context) {
    m_pCamera = new Camera(width, height);
    addObject(m_pCamera);
    auto obj = new GameObject();

    /*auto texture = sf::RenderTexture();
    texture.create(sf::Vector2u(30, 30)); // размер текстуры

    // Создаем круг на текстуре
    sf::CircleShape circle(15.f);
    circle.setFillColor(sf::Color::Red);
    circle.setPosition(sf::Vector2f(0.f, 0.f));

    // Рисуем круг на текстуре
    texture.clear(sf::Color::Transparent);
    texture.draw(circle);
    texture.display();
    auto *tex = new sf::Texture();
    tex->create(sf::Vector2u(30, 30));
    tex->update(texture.getTexture());*/

    obj->setTexture("/media/sireth/F0CE491ACE48DA8C/Projects/CppProjects/Pong/cmake-build-debug/img.png");
    obj->setScale({0.1,0.1,0.1});
    obj->setPosition({0, 0,10});
    addObject(obj);
}
Camera *Scene::getCamera() {
    return m_pCamera;
}
void Scene::on_update() {
    std::unique_lock<std::mutex> lock(m_gameObjects_mutex);
    std::for_each(m_gameObjects.begin(), m_gameObjects.end(), [](GameObject *gameObject){
        gameObject->fixedUpdate();
    });
}
