#include "../../headers/templates/Button.h"

#include <utility>

#include "../../headers/Context.h"
#include "../../headers/Log.h"
#include "../../headers/utils.h"

Button::Button(glm::vec2 size, sf::Color color)
    : m_size(size), m_backgroundColor(color) {
    if (!m_font.loadFromFile(getDefaultFontPath())) {
        LOG_CRITICAL("We can't load font from file!");
    }
    m_text = new sf::Text(m_font, "a");
    updateTextureBackground();
}
Button::Button(sf::Text text, glm::vec2 size, sf::Color color)
    : m_text(new sf::Text(std::move(text))),
      m_size(size),
      m_backgroundColor(color) {
    m_font = sf::Font(*m_text->getFont());
    updateTextureBackground();
}
void Button::setText(const std::string& string) {
    m_text->setString(string);
    updateTextureBackground();
}
void Button::setText(sf::Text text) {
    delete m_text;
    m_text = new sf::Text(std::move(text));
    m_font = *m_text->getFont();
    updateTextureBackground();
}
void Button::setFont(sf::Font font) {
    m_font = std::move(font);
    updateTextureBackground();
}
void Button::setSize(glm::vec2 size) {
    m_size = size;
    updateTextureBackground();
}
void Button::setBackgroundColor(sf::Color color) {
    m_backgroundColor = color;
    updateTextureBackground();
}
void Button::setBackground(const sf::Texture& texture) {
    auto background = new sf::Texture(texture);
    auto size = background->getSize();
    m_size = {size.x, size.y};
    updateTextureBackground(background);
}
void Button::updateTextureBackground() {
    sf::RectangleShape rectangle({m_size.x, m_size.y});
    rectangle.setFillColor(m_backgroundColor);
    sf::Font font;

    sf::RenderTexture renderTexture;
    if (renderTexture.create({static_cast<unsigned>(m_size.x),
                              static_cast<unsigned>(m_size.y)})) {
        /// Centering Text
        sf::FloatRect textRect = m_text->getLocalBounds();
        m_text->setOrigin({textRect.left + textRect.width / 2.0f,
                           textRect.top + textRect.height / 2.0f});
        m_text->setPosition({m_size.x / 2, m_size.y / 2});
        renderTexture.clear(sf::Color::Transparent);
        renderTexture.draw(rectangle);

        renderTexture.draw(*m_text);

        renderTexture.display();
        auto texture = new sf::Texture(renderTexture.getTexture());
        setTexture(texture);
    } else {
        LOG_CRITICAL("Background of button did not create!");
    }
}
void Button::updateTextureBackground(sf::Texture* texture) {
    sf::RenderTexture renderTexture;
    sf::Sprite sprite(*texture);
    if (renderTexture.create({static_cast<unsigned>(m_size.x),
                              static_cast<unsigned>(m_size.y)})) {
        /// Centering Text
        sf::FloatRect textRect = m_text->getLocalBounds();
        m_text->setOrigin({textRect.left + textRect.width / 2.0f,
                           textRect.top + textRect.height / 2.0f});
        m_text->setPosition({m_size.x / 2, m_size.y / 2});
        renderTexture.clear(sf::Color::Transparent);
        renderTexture.draw(sprite);

        renderTexture.draw(*m_text);

        renderTexture.display();
        delete texture;
        texture = new sf::Texture(renderTexture.getTexture());
        setTexture(texture);
    } else {
        LOG_CRITICAL("Background of button did not create!");
    }
}
bool isPointInsideRectangle(const glm::vec2& point, const glm::vec2& rectMin,
                            const glm::vec2& rectMax) {
    return point.x >= rectMin.x && point.x <= rectMax.x &&
           point.y >= rectMin.y && point.y <= rectMax.y;
}
void Button::checkMouseActions() {
    auto context = m_pScene->getContext();
    glm::vec3 mousePos{context->getMousePosition(), 0};
    auto btnPos = getPosition();
    mousePos = context->screenToWorldPoint(mousePos);

    m_actions[Up] = false;
    m_actions[Click] = false;
    m_actions[Out] = false;
    if (isPointInsideRectangle(mousePos, glm::vec2(btnPos) - m_size / 2.f,
                               glm::vec2(btnPos) + m_size / 2.f)) {
        m_actions[Over] = true;
        if (context->isMouseKeyPressed(sf::Mouse::Left)) {
            m_actions[Down] = true;
        }
    }
    else if(m_actions[Over]){
        m_actions[Over] = false;
        m_actions[Out] = true;
    }

    if(m_actions[Down]){
        if(!context->isMouseKeyPressed(sf::Mouse::Left)){
            m_actions[Down] = false;
            m_actions[Up] = true;
            if (isPointInsideRectangle(mousePos, glm::vec2(btnPos) - m_size / 2.f,
                                       glm::vec2(btnPos) + m_size / 2.f)) {
                m_actions[Click] = true;
            }
        }
    }
}
void Button::update() {
    GameObject::update();
    checkMouseActions();
    startMouseFunctions();
}

void Button::setMouseClickAction(std::function<void()> action) {
    m_actionFunctions[Mouse::Click] = std::move(action);
}
void Button::setMouseDownAction(std::function<void()> action) {
    m_actionFunctions[Mouse::Down] = std::move(action);
}
void Button::setMouseUpAction(std::function<void()> action) {
    m_actionFunctions[Mouse::Up] = std::move(action);
}
void Button::setMouseOverAction(std::function<void()> action) {
    m_actionFunctions[Mouse::Over] = std::move(action);
}
void Button::setMouseOutAction(std::function<void()> action) {
    m_actionFunctions[Mouse::Out] = std::move(action);
}
void Button::startMouseFunctions() {
    if(m_actions[Click]){
        m_actionFunctions[Click]();
    }
    if(m_actions[Down]){
        m_actionFunctions[Down]();
    }
    if(m_actions[Up]){
        m_actionFunctions[Up]();
    }
    if(m_actions[Over]){
        m_actionFunctions[Over]();
    }
    if(m_actions[Out]){
        m_actionFunctions[Out]();
    }
}

