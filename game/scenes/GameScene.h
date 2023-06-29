#ifndef GOLF_GAMESCENE_H
#define GOLF_GAMESCENE_H

#pragma once

#include "../../headers/Scene.h"


class GameScene: public Scene{
    std::string m_playerName;

   public:
    GameScene(float width, float height, Context *context);
};

#endif  // GOLF_GAMESCENE_H
