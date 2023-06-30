#ifndef GOLF_CHECKEND_H
#define GOLF_CHECKEND_H
#pragma once
#include "../../headers/Component.h"
class CheckEnd: public Component {
   public:
    void start() override;
    void update() override;
    void fixedUpdate() override;
};

#endif  // GOLF_CHECKEND_H
