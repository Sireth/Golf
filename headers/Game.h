#ifndef GOLF_GAME_H
#define GOLF_GAME_H
#pragma once

#include <memory>
#include <include/BS_thread_pool.hpp>

class Context;
class Window;

class Game {
   public:
    Game();
    virtual ~Game();

    Game(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(const Game&) = delete;
    Game& operator=(Game&&) = delete;

    void start();
    void stop();
    void on_render();
    void on_update();
    void on_eventsUpdate();

    protected:
    std::unique_ptr<Window> m_pWindow;
    BS::thread_pool m_renderThreadPool{1};
    BS::thread_pool m_updateThreadPool{1};
    BS::thread_pool m_eventsUpdateThreadPool{1};

    Context * m_pGameContext;
};

#endif  // GOLF_GAME_H
