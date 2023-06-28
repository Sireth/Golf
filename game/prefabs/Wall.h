#ifndef GOLF_WALL_H
#define GOLF_WALL_H

#pragma once

#include "../../headers/GameObject.h"


class Wall: public GameObject {
    int m_group;
    int m_number;
};

#endif  // GOLF_WALL_H
