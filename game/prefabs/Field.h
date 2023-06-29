#ifndef GOLF_FIELD_H
#define GOLF_FIELD_H

#pragma once

#include <box2d/box2d.h>

#include "../../headers/GameObject.h"

class Wall;
class Ball;
class Hole;

class Field: public GameObject {
    std::list <Wall *> m_walls;

    Ball *m_pBall= nullptr;
    Hole *m_pHole= nullptr;

    uint m_level = 1;
    bool m_left = false;

    bool neededReload = false;


    b2World m_world{{0,0}};

    void loadFromFile();

    glm::vec3 localToWorldPosition(glm::vec2 pos);

    class ContactListener: public b2ContactListener{
       public:
        explicit ContactListener(Field *field):m_field(field){};
        Field *m_field;
        void BeginContact(b2Contact* contact) override;
        void EndContact(b2Contact* contact) override;
    };

    ContactListener m_contactListener{this};

   public:
    Field(bool isLeft, uint level);

    void start() override;

    void setLevel(uint level);

    void reload(){ neededReload =true;}

    void fixedUpdate() override;
};

#endif  // GOLF_FIELD_H
