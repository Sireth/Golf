#ifndef GOLF_WALL_H
#define GOLF_WALL_H

#pragma once

#include "../../headers/GameObject.h"
#include "Field.h"

class Wall : public GameObject {
    int m_group;
    int m_number;

   public:
    explicit Wall(unsigned char group = 1, unsigned char number = 1);

    void setLocalPosition(glm::vec2 pos, GameObject *field);

   private:
    void loadWallTexture();
};

#endif  // GOLF_WALL_H
