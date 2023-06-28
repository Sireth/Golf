#ifndef GOLF_FIELD_H
#define GOLF_FIELD_H

#pragma once

#include "../../headers/GameObject.h"

class Wall;

class Field: public GameObject {
    std::list <Wall *> m_walls;
    uint m_level = 1;
    bool m_left = false;

    void loadFromFile();
   public:
    Field(bool isLeft, uint level);

    void start() override;

    void setLevel(uint level);
};

#endif  // GOLF_FIELD_H
