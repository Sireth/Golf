#ifndef GOLF_MENU_H
#define GOLF_MENU_H

#pragma once

#include "../../headers/Scene.h"

class Menu: virtual public Scene {
    std::string m_playerName;
   public:
    Menu(float width, float height, Context *context);
};

#endif  // GOLF_MENU_H
