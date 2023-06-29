#include "../headers/Game.h"

#include "../headers/Context.h"
#include "../headers/Log.h"



Game::Game() : m_pGameContext(new Context()) {
    ///Needed to create Window and Scene
    ///
    /// \details
    /// \code m_pWindow = std::make_unique<Window>("Game", 1280, 720, m_pGameContext);
    /// m_pWindow->setCurrentScene(new Scene(1280, 720, m_pGameContext));
    /// m_pGameContext->setGame(this);
    /// \endcode
}

Game::~Game() = default;

void Game::start() {
    m_pGameContext->m_running = true;
    on_eventsUpdate();

    std::chrono::steady_clock::time_point now =
        std::chrono::steady_clock::now();

    std::chrono::steady_clock::time_point renderDeltaTime = now;
    std::chrono::steady_clock::time_point updateDeltaTime = now;
    std::chrono::steady_clock::time_point eventsDeltaTime = now;
    std::chrono::steady_clock::time_point FpsDelta = now;
    int fps = 0;

    while (m_pGameContext->getRunning()) {
        now = std::chrono::steady_clock::now();
        m_pGameContext->deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(now - renderDeltaTime).count();
        if (m_pGameContext->deltaTime >= 1000 / 144) {
            renderDeltaTime = std::chrono::steady_clock::now();
            auto _1 = m_renderThreadPool.submit([this, &fps] {
                on_render();
                fps++;
            });
        }
        now = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(
                now - updateDeltaTime)
                .count() >= 20) {
            updateDeltaTime = std::chrono::steady_clock::now();
            auto _2 = m_updateThreadPool.submit([this] {
                on_update();
            });
        }
        now = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - eventsDeltaTime).count() >= 1) {
            eventsDeltaTime = std::chrono::steady_clock::now();
            auto _3 =m_eventsUpdateThreadPool.submit([this] {
                on_eventsUpdate();
            });
        }
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - FpsDelta).count() >= 1000) {
            LOG_INFO("FPS: {0}", fps);
            fps = 0;
            FpsDelta = std::chrono::steady_clock::now();
        }
    }

    stop();
}

void Game::on_render() { m_pWindow->on_update(); }
void Game::on_update() { m_pWindow->on_updateScene(); }
void Game::on_eventsUpdate() { m_pWindow->on_updateEvents(); }
void Game::stop() {
    LOG_INFO("Stopping game...");
    m_pGameContext->stopGame();
    m_renderThreadPool.wait_for_tasks();
    m_updateThreadPool.wait_for_tasks();
    m_eventsUpdateThreadPool.wait_for_tasks();
    m_pWindow->shutdown();
    LOG_INFO("Game stopped");
}
