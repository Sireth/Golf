#include "ExitGameScript.h"

#include "../../headers/Context.h"
#include "../../headers/GameObject.h"
#include "../../headers/Log.h"

void ExitGameScript::start() {}
void ExitGameScript::update() {}
void ExitGameScript::fixedUpdate() {
    auto context = this->gameObject->getContext();
    if(context->getEvent().type == sf::Event::Closed){
        context->stopGame();
        LOG_INFO("Stop game");
    }
}
