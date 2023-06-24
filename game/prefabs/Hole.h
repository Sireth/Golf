#ifndef PONG_HOLE_H
#define PONG_HOLE_H

#include "../../headers/GameObject.h"

class Hole: public GameObject{
   public:
    enum {
        RADIUS = 30,
    };
    Hole(glm::vec3 position);

    char bonus = 1;
};


#endif  // PONG_HOLE_H
