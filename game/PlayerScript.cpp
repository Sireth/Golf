#include "PlayerScript.h"

#include "../headers/Context.h"
#include "../headers/GameObject.h"
#include "../headers/Log.h"
#include "SFML/Graphics.hpp"
#include "glm/gtx/compatibility.hpp"
#include <glm/gtx/vector_angle.hpp>

#include "prefabs/Ball.h"

void PlayerScript::start() {

    powerRow = new PowerRow();

    powerRow->active = false;
    gameObject->m_pScene->addObject(powerRow);
}
void PlayerScript::update() {

}
void PlayerScript::fixedUpdate() {

    auto context = this->gameObject->getContext();

    if(context->isMouseKeyPressed(sf::Mouse::Button::Left)){
        if(!leftMousePressed){
            powerRow->active = true;
            leftMousePressed = true;
            oldMousePos = context->getMousePosition();
        }
        mousePos = context->getMousePosition();
        auto normal = glm::normalize(oldMousePos - mousePos) * glm::vec2(1, -1);

        powerRow->setPosition(gameObject->getPosition() + glm::vec3(normal * powerRow->m_size.x/2.f,0));
        powerRow->setRotation({0,0, glm::degrees(abs(glm::angle(normal, glm::vec2(1,0)))) * -abs(normal.y)/normal.y});
    }
    if(!context->isMouseKeyPressed(sf::Mouse::Button::Left)){
        if(leftMousePressed){
            powerRow->active = false;
            leftMousePressed = false;

            auto vel = (oldMousePos - mousePos) * glm::vec2(1, -1) /10.f;
            reinterpret_cast<Ball *>(this->gameObject)->m_body->ApplyForceToCenter({vel.x,vel.y}, true);
        }
    }

}
