#include "../headers/Window.h"

#include <SFML/Graphics.hpp>

#include "../headers/GameObject.h"
#include "../headers/Log.h"
#include "../headers/Scene.h"
#include "../headers/utils.h"

Window::Window(std::string title, const unsigned int width,
               const unsigned int height, Context &context): m_gameContext(context) {
    m_data = {std::move(title), width, height};
    LOG_INFO("Creating window \"{0}\" with size {1}x{2}...", m_data.title,
             m_data.width, m_data.height);
    int resultCode = init();
    LOG_INFO("Window \"{0}\" created!", m_data.title);
    m_pCurrentScene = nullptr;
}

Window::~Window() { shutdown(); }
void Window::on_update() {
    LOG_INFO("Update window \"{0}\"", m_data.title);
    m_viewMatrix = m_pCurrentScene->getCamera()->getViewMatrix();
    {
        std::unique_lock<std::mutex> lock(m_pWindow_mutex);
        m_pWindow->clear();
    }
    std::for_each(++m_pCurrentScene->getGameObjectBeginIterator(),
                  m_pCurrentScene->getGameObjectEndIterator(),
                  [this](GameObject *gameObject) {
                      renderObject(gameObject);
                      gameObject->update();
                  });

    std::unique_lock<std::mutex> lock(m_pWindow_mutex);
    m_pWindow->display();
}

int Window::init() {
    std::unique_lock<std::mutex> lock(m_pWindow_mutex);
    m_pWindow = new sf::RenderWindow(
        sf::VideoMode(sf::Vector2u(m_data.width, m_data.height)), m_data.title);
    if (!m_pWindow) {
        LOG_CRITICAL("Can't create window {0} with size {1}x{2}", m_data.title,
                     m_data.width, m_data.height);
        return -1;
    }
    return 0;
}

void Window::shutdown() {
    std::unique_lock<std::mutex> lock(m_pWindow_mutex);
    if (m_pWindow) {
        m_pWindow->close();
        delete m_pWindow;
        m_pWindow = nullptr;
        LOG_INFO("Window \"{0}\" was closed", m_data.title);
        return;
    }
    LOG_ERROR("Window \"{0}\" already closed", m_data.title);
}
void Window::renderObject(GameObject *gameObject) {
    gameObject->lockTextureMutex();
    sf::Texture *texture = gameObject->getTexture();

    bool deleteTextureFlag = false;

    if (!texture) {
        LOG_ERROR("We don have a texture!");
        texture = new sf::Texture();
        if (!texture->create(sf::Vector2u(10, 10))) {
            LOG_CRITICAL("We dont create texture");
        }
        deleteTextureFlag = true;
    }

    sf::Sprite sprite(*texture);
    auto size = texture->getSize();
    gameObject->unlockTextureMutex();
    sprite.setPosition(
        {-static_cast<float>(size.x) / 2, -static_cast<float>(size.y) / 2});

    if (deleteTextureFlag) {
        delete texture;
    }

    std::unique_lock<std::mutex> lock(m_pWindow_mutex);

    m_pWindow->draw(sprite, glmMat4ToSfTransform(m_viewMatrix *
                                                 gameObject->getTransform()));
}
void Window::setCurrentScene(Scene *scene) { m_pCurrentScene = scene; }
void Window::on_updateScene() { m_pCurrentScene->on_update(); }
