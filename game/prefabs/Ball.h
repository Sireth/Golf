#ifndef GOLF_BALL_H
#define GOLF_BALL_H

#pragma once

#include <box2d/box2d.h>

#include "../../headers/GameObject.h"

class Ball: public GameObject{
   public:

    bool player = false;
    Ball();

    void fixedUpdate() override;

    b2Body* m_body = nullptr;
};

#endif  // GOLF_BALL_H
