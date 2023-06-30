#ifndef GOLF_GAMESCENE_H
#define GOLF_GAMESCENE_H

#pragma once

#include "../../headers/Scene.h"
#include "../prefabs/Field.h"
#include "Menu.h"

class GameScene: public Scene{
    std::string m_playerName;
   public:
    int m_score = 0;
    int m_strokesCount = 1;

    Field *m_leftField;
    Field *m_rightField;

    Menu *m_menu;

   public:
    GameScene(float width, float height, Context *context, Menu *menu);

};

#endif  // GOLF_GAMESCENE_H
