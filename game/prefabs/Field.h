#ifndef GOLF_FIELD_H
#define GOLF_FIELD_H

#pragma once

#include "../../headers/GameObject.h"


class Field: public GameObject {
    std::list <Wall *> m_walls;
};

#endif  // GOLF_FIELD_H
