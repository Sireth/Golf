#include "../headers/Game.h"

#include "../headers/Scene.h"
#include "../headers/Window.h"
#include "SFML/System.hpp"

Game::Game() {
    m_pWindow = std::make_unique<Window>("Pong", 1280, 720);
    m_pWindow->setCurrentScene(
        new Scene(1280, 720, <#initializer #>, <#initializer #>));
}


Game::~Game() {
}

int Game::start() {
    m_running = true;
    while (m_running){
        auto _1 = m_renderThreadPool.submit([this]{ on_render();});
        auto _2 = m_updateThreadPool.submit([this]{ on_update();});
        auto _3 = m_eventsUpdateThreadPool.submit([this]{ on_eventsUpdate();});
        sf::sleep(sf::milliseconds(10));
    }
}
void Game::on_render() {
    m_pWindow->on_update();
}
void Game::on_update() {
    m_pWindow->on_updateScene();
}
void Game::on_eventsUpdate() {

}
int Game::stop() {
    m_running = false;
    m_renderThreadPool.wait_for_tasks();
    m_updateThreadPool.wait_for_tasks();
    m_eventsUpdateThreadPool.wait_for_tasks();
    m_pWindow->shutdown();
}
