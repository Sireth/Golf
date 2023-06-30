#ifndef GOLF_MENU_H
#define GOLF_MENU_H

#pragma once

#include "../../headers/Scene.h"
#include "../../headers/templates/Button.h"

class Menu: virtual public Scene {
    std::string m_playerName;
    std::list<Button *> m_leaders;
   public:
    Menu(float width, float height, Context *context);
    void updateLeaders();
};

#endif  // GOLF_MENU_H
