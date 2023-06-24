#include "../headers/Scene.h"

#include <algorithm>

#include "../game/CameraScript.h"
#include "../game/ExitGameScript.h"
#include "../game/PlayerScript.h"
#include "../game/prefabs/Ball.h"
#include "../game/prefabs/Collision.h"
#include "../headers/Camera.h"
#include "../headers/Context.h"
#include "../headers/Log.h"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RenderTexture.hpp"

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
    m_pCamera->addComponent(new ExitGameScript());
    addObject(m_pCamera);

    auto collision = new Collision();

    auto mainBall = new Ball(0,  glm::vec3(1,1,1));
    mainBall->addComponent(new PlayerScript());
    addObject(mainBall);
    collision->addBall(mainBall);

    auto ball1 = new Ball(15,  glm::vec3(-250, 0,1));
    addObject(ball1);
    collision->addBall(ball1);

    auto ball2 = new Ball(1,  glm::vec3(-302, 0,1));
    addObject(ball2);
    collision->addBall(ball2);

    auto ball3 = new Ball(2,  glm::vec3(-354, 0,1));
    addObject(ball3);
    collision->addBall(ball3);

    auto ball4 = new Ball(3,  glm::vec3(-276, 15,1));
    addObject(ball4);
    collision->addBall(ball4);

    auto ball5 = new Ball(4,  glm::vec3(-276, -15,1));
    addObject(ball5);
    collision->addBall(ball5);

    auto ball6 = new Ball(5,  glm::vec3(-328, -15,1));
    addObject(ball6);
    collision->addBall(ball6);

    auto ball7 = new Ball(6,  glm::vec3 (-328, 15,1));
    addObject(ball7);
    collision->addBall(ball7);

    auto ball8 = new Ball(7,  glm::vec3(-302, 30,1));
    addObject(ball8);
    collision->addBall(ball8);

    auto ball9 = new Ball(8,  glm::vec3(-302, -30,1));
    addObject(ball9);
    collision->addBall(ball9);

    auto ball10 = new Ball(9,  glm::vec3(-354, 30,1));
    addObject(ball10);
    collision->addBall(ball10);

    auto ball11 = new Ball(10,  glm::vec3(-354, -30,1));
    addObject(ball11);
    collision->addBall(ball11);

    auto ball12 = new Ball(11,  glm::vec3(-328, -45,1));
    addObject(ball12);
    collision->addBall(ball12);

    auto ball13 = new Ball(12,  glm::vec3(-328, 45,1));
    addObject(ball13);
    collision->addBall(ball13);


    auto ball14 = new Ball(13,  glm::vec3(-354, 60,1));
    addObject(ball14);
    collision->addBall(ball14);


    auto ball15 = new Ball(14,  glm::vec3(-354, -60,1));
    addObject(ball15);
    collision->addBall(ball15);

    auto wallTop = new Rectangle(glm::vec3(0, 250, 1), glm::vec2(1000, 100),
                              sf::Color::Green);
    addObject(wallTop);
    collision->addWall(wallTop);

    auto wallDown = new Rectangle(glm::vec3(0, -250, 1), glm::vec2(1000, 100),
                              sf::Color::Green);
    addObject(wallDown);
    collision->addWall(wallDown);

    auto wallRight = new Rectangle(glm::vec3(500, 0, 1), glm::vec2(100, 500),
                              sf::Color::Green);
    addObject(wallRight);
    collision->addWall(wallRight);

    auto wallLeft = new Rectangle(glm::vec3(-500, 0, 1), glm::vec2(100, 500),
                              sf::Color::Green);
    addObject(wallLeft);
    collision->addWall(wallLeft);

    auto obj4 = new GameObject();
    obj4->setTexture(
        "/home/adtema/CLionProjects/Golf/"
        "1674270773_catherineasquithgallery-com-p-serii-fon-tekstura-bumagi-"
        "foto-104.jpg");
    obj4->setPosition({0, 0, -50});
    addObject(obj4);

    addObject(collision);
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
