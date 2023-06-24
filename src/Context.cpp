#include "../headers/Context.h"

#include <utility>

#include "../headers/Camera.h"
#include "../headers/utils.h"

Context::Context() {
    m_defaultFont.loadFromFile(getDefaultFontPath());
}
void Context::setWindowData(Context::WindowData win_data) {
    m_mainWidowData = std::move(win_data);
}
void Context::stopGame() { m_running = false; }
bool Context::isKeyPressed(sf::Keyboard::Key keyCode) {
    return m_pressedKeys[static_cast<int>(keyCode)];
}
void Context::setKeyPressed(sf::Keyboard::Key keyCode) {
    m_pressedKeys[static_cast<int>(keyCode)] = true;
}
void Context::setKeyReleased(sf::Keyboard::Key keyCode){
    m_pressedKeys[static_cast<int>(keyCode)] = false;
}
[[maybe_unused]] bool Context::isMouseKeyPressed(sf::Mouse::Button keyCode) {
    return m_pressedMouseKeys[keyCode];
}
void Context::setMouseKeyPressed(sf::Mouse::Button keyCode) {
    m_pressedMouseKeys[keyCode] = true;
}
void Context::setMouseKeyReleased(sf::Mouse::Button keyCode) {
    m_pressedMouseKeys[keyCode] = false;
}
void Context::updateMousePosition(glm::vec2 mousePosition) {
    m_mousePosition = mousePosition;
}
glm::vec2 Context::getMousePosition() {
    return m_mousePosition;
}
void Context::setCamera(Camera *camera) {
    m_pCamera = camera;
}
glm::vec3 Context::screenToWorldPoint(glm::vec2 pos) {
    auto camPos = m_pCamera->getPosition();
    return (glm::vec3(pos, 0) + camPos - glm::vec3(m_mainWidowData.width / 2,m_mainWidowData.height / 2, 0))*glm::vec3(1,-1,1);

}
