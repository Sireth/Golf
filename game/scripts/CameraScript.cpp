#include "CameraScript.h"

#include "../../headers/Context.h"
#include "../../headers/GameObject.h"
#include "../../headers/Log.h"
#include "glm/gtx/compatibility.hpp"

void CameraScript::start() {}
void CameraScript::update() {}
void CameraScript::fixedUpdate() {


    float moveSpeed = 10.0f;
    float smooth = 0.05f;

    glm::vec3 oldPosition = gameObject->getPosition();


    auto context = this->gameObject->getContext();

    if (context->isKeyPressed(sf::Keyboard::Left))
    {
        position = position + glm::vec3(-moveSpeed, 0.0f, 0.0f);
    }
    if (context->isKeyPressed(sf::Keyboard::Right))
    {
        position = position + glm::vec3(moveSpeed, 0.0f, 0.0f);
    }
    if (context->isKeyPressed(sf::Keyboard::Up))
    {
        position = position + glm::vec3(0.0f, -moveSpeed, 0.0f);
    }
    if (context->isKeyPressed(sf::Keyboard::Down))
    {
        position = position + glm::vec3(0.0f, moveSpeed, 0.0f);
    }

    oldPosition = glm::lerp(oldPosition, position, smooth);
    gameObject->setPosition(oldPosition);
}
