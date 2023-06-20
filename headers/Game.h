#ifndef PONG_GAME_H
#define PONG_GAME_H
#pragma once

#include <memory>

#include "Context.h"
#include "include/BS_thread_pool.hpp"

class Window;

class Game {
   public:
    Game();
    virtual ~Game();

    Game(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(const Game&) = delete;
    Game& operator=(Game&&) = delete;

    [[noreturn]] int start();
    [[noreturn]] int stop();
    void on_render();
    void on_update();
    void on_eventsUpdate();

   private:
    std::unique_ptr<Window> m_pWindow;
    BS::thread_pool m_renderThreadPool{1};
    BS::thread_pool m_updateThreadPool{1};
    BS::thread_pool m_eventsUpdateThreadPool{1};

    bool m_running;
    Context &m_gameContext;
};

#endif  // PONG_GAME_H
