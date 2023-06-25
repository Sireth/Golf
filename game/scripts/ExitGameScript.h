#ifndef PONG_EXITGAMESCRIPT_H
#define PONG_EXITGAMESCRIPT_H

#pragma once

#include "../../headers/Component.h"

class ExitGameScript: public Component {
   public:
    void start() override;
    void update() override;
    void fixedUpdate() override;
};

#endif  // PONG_EXITGAMESCRIPT_H
