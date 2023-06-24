#ifndef PONG_POWERROW_H
#define PONG_POWERROW_H

#include "../../headers/GameObject.h"

class PowerRow: public GameObject {
   public:
    PowerRow();

    glm::vec2 m_size{70, 2};
};

#endif  // PONG_POWERROW_H
