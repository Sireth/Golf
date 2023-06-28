#include "../headers/Window.h"

#include <SFML/Graphics.hpp>
#include <utility>

#include "../headers/GameObject.h"
#include "../headers/Log.h"
#include "../headers/utils.h"
#include "../headers/Camera.h"
#include "../headers/Context.h"


Window::Window(std::string title, const unsigned int width,
               const unsigned int height, Context *context): m_pGameContext(context) {
    m_pGameContext->setWindowData({std::move(title), width, height});
    auto data = m_pGameContext->getWindowData();
    LOG_INFO("Creating window \"{0}\" with size {1}x{2}...", data.title,
             data.width, data.height);
    if(init() == -1){
        LOG_CRITICAL("Window don't create!");
        m_pGameContext->stopGame();
    }
    LOG_INFO("Window \"{0}\" created!", data.title);
    m_pCurrentScene = nullptr;
}
Window::~Window() {
    shutdown();
}
void Window::on_update() {
    m_viewMatrix = m_pGameContext->m_pCamera->getViewMatrix();
    {
        std::unique_lock<std::mutex> lock(m_pWindow_mutex);
        m_pWindow->clear();
    }
    {
        std::unique_lock<std::mutex> lock(m_pCurrentScene->m_gameObjects_mutex);
            std::for_each(
        m_pCurrentScene->m_gameObjects.begin(),
        m_pCurrentScene->m_gameObjects.end(),
        [this](GameObject *gameObject) {
                if(gameObject) {
                    renderObject(gameObject);
                    gameObject->update();
                }
        });
    }
    std::unique_lock<std::mutex> lock(m_pWindow_mutex);
    m_pWindow->display();
}

int Window::init() {
    std::unique_lock<std::mutex> lock(m_pWindow_mutex);
    auto data = m_pGameContext->getWindowData();
    m_pWindow = new sf::RenderWindow(
        sf::VideoMode({data.width, data.height}), data.title, sf::Style::Close, sf::ContextSettings(8,8,8));

    if (!m_pWindow) {
        LOG_CRITICAL("Can't create window {0} with size {1}x{2}", data.title,
                     data.width, data.height);
        return -1;
    }
    return 0;
}

void Window::shutdown() {
    std::unique_lock<std::mutex> lock(m_pWindow_mutex);
    auto data = m_pGameContext->getWindowData();

    if (m_pWindow) {
        m_pWindow->close();
        delete m_pWindow;
        m_pWindow = nullptr;
        LOG_INFO("Window \"{0}\" was closed", data.title);
        return;
    }
    LOG_ERROR("Window \"{0}\" already closed", data.title);
}
void Window::renderObject(GameObject *gameObject) {
    gameObject->lockTextureMutex();
    sf::Texture *texture = gameObject->getTexture();

    if (!texture || !gameObject->active) {
        gameObject->unlockTextureMutex();
        return;
    }

    sf::Sprite sprite(*texture);
    auto size = texture->getSize();
    gameObject->unlockTextureMutex();
    sprite.setPosition(
        {-static_cast<float>(size.x) / 2, -static_cast<float>(size.y) / 2});


    std::unique_lock<std::mutex> lock(m_pWindow_mutex);
    auto gm_t = gameObject->getTransform();
    gm_t[3][1] = -gm_t[3][1];
    m_pWindow->draw(sprite, glmMat4ToSfTransform(m_viewMatrix * gm_t));
}
void Window::setCurrentScene(Scene *scene) {
    m_pCurrentScene = scene;
}
void Window::on_updateScene() const {
    m_pCurrentScene->on_update();
}
void Window::on_updateEvents() {
    std::unique_lock<std::mutex> lock(m_pWindow_mutex);
    if(!m_pWindow->pollEvent(m_pGameContext->getEvent())) return;
    auto event = m_pGameContext->getEvent();
    if(event.type == sf::Event::KeyPressed){
        m_pGameContext->setKeyPressed(event.key.code);
    }
    if(event.type == sf::Event::KeyReleased){
        m_pGameContext->setKeyReleased(event.key.code);
    }
    if(event.type == sf::Event::MouseButtonPressed){
        m_pGameContext->setMouseKeyPressed(event.mouseButton.button);
    }
    if(event.type == sf::Event::MouseButtonReleased){
        m_pGameContext->setMouseKeyReleased(event.mouseButton.button);
    }
    if(event.type == sf::Event::MouseMoved){
        m_pGameContext->updateMousePosition({event.mouseMove.x, event.mouseMove.y});
    }
    if(event.type == sf::Event::Closed){
        m_pGameContext->stopGame();
    }
}
[[maybe_unused]] unsigned int Window::get_height() const {
    auto data = m_pGameContext->getWindowData();
    return data.height;
}
[[maybe_unused]] unsigned int Window::get_width() const {
    auto data = m_pGameContext->getWindowData();
    return data.width;
}
