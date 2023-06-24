#ifndef PONG_COLLISION_H
#define PONG_COLLISION_H

#pragma once

#include "../../headers/GameObject.h"
#include "Ball.h"
#include "Rectangle.h"
#include "Hole.h"
#include "box2d/box2d.h"

class Collision: public GameObject {
   public:
    void fixedUpdate() override;
    void addBall(Ball * ball);
    void addWall(Rectangle * wall);
    void addHole(Hole * hole);


    std::list<Ball *> m_balls;
    std::list<Rectangle *> m_walls;
    std::list<Hole *> m_hols;

    b2World world{{0,0}};


};


#endif  // PONG_COLLISION_H
