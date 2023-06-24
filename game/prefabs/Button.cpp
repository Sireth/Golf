#include "Button.h"

#include <utility>

#include "../../headers/Context.h"


Button::Button(glm::vec2 size, sf::Color color, std::function<void()> action)
    : m_text(m_pScene->getContext()->getDefaultFont()),
      m_size(size),
      m_backgroundColor(color),
      m_action(std::move(action)) {

    //TODO: draw texture
}

Button::Button(sf::Text text, glm::vec2 size, sf::Color color,
               std::function<void()> action)
    : m_text(std::move(text)),
      m_size(size),
      m_backgroundColor(color),
      m_action(std::move(action)) {

    //TODO: draw texture
}
void Button::setText(const std::string& string) {
    m_text.setString(string);
}
void Button::setText(sf::Text text) {
    m_text = std::move(text);
    m_font = *m_text.getFont();
}
void Button::setFont(sf::Font font) {
    m_font = std::move(font);
}
void Button::setAction(std::function<void()> action) {
    m_action = std::move(action);
}
void Button::setSize(glm::vec2 size) {
    m_size = size;
}
void Button::setBackgroundColor(sf::Color color) {
    m_backgroundColor = color;

    //TODO: redraw texture
}
sf::Texture Button::createTexture() {
    ///////////
}
