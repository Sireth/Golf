#ifndef PONG_CAMERA_H
#define PONG_CAMERA_H

#pragma once

#include "GameObject.h"


class Camera : public GameObject {
   public:
    Camera(float width, float height);


   public:
    float m_width2;
    float m_height2;
    glm::mat4 getViewMatrix();
};

#endif  // PONG_CAMERA_H
