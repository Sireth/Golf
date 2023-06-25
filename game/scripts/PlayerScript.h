#ifndef PONG_PLAYERSCRIPT_H
#define PONG_PLAYERSCRIPT_H

#pragma once

#include "../../headers/Component.h"
#include "../prefabs/PowerRow.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

class PlayerScript: public Component  {
   public:
    void start() override;
    void update() override;
    void fixedUpdate() override;

    bool leftMousePressed = false;

    PowerRow *powerRow = nullptr;

    glm::vec2 mousePos;
    glm::vec2 oldMousePos;

};

#endif  // PONG_PLAYERSCRIPT_H
