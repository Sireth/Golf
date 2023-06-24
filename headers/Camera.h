#ifndef GOLF_CAMERA_H
#define GOLF_CAMERA_H

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

#endif  // GOLF_CAMERA_H
