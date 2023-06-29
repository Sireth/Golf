#ifndef GOLF_WALL_H
#define GOLF_WALL_H

#pragma once

#include "../../headers/GameObject.h"
#include "Field.h"

class Wall : public GameObject {
    int m_group;
    int m_number;

   public:
    b2Body* m_body = nullptr;

   public:
    explicit Wall(unsigned char group = 1, unsigned char number = 1);

    void setLocalPosition(glm::vec2 pos, GameObject *field);

    int getGroup() const{return m_group;};

   private:
    void loadWallTexture();
};

#endif  // GOLF_WALL_H
