#ifndef PONG_CAMERASCRIPT_H
#define PONG_CAMERASCRIPT_H

#pragma once

#include "../../headers/Component.h"
#include "glm/vec3.hpp"

class CameraScript: public Component {
   public:
    void start() override;
    void update() override;
    void fixedUpdate() override;

    glm::vec3 position;
};

#endif  // PONG_CAMERASCRIPT_H
