#include "../../headers/templates/Text.h"

#include "../../headers/Log.h"
#include "../../headers/utils.h"

Text::Text() {
    auto font = new sf::Font();
    if(!font->loadFromFile(getDefaultFontPath())){
        LOG_ERROR("Did not load font!");
    }
    m_pText = std::make_unique<sf::Text>(*font);
    updateTextTexture();
}
Text::Text(const sf::Text& text) {
    m_pText = std::make_unique<sf::Text>(text);
    updateTextTexture();
}
Text::Text(const std::string& string, unsigned characterSize) {
    auto font = new sf::Font();
    if(!font->loadFromFile(getDefaultFontPath())){
        LOG_ERROR("Did not load font!");
    }
    m_pText = std::make_unique<sf::Text>(*font, sf::String::fromUtf8(string.begin(), string.end()), characterSize);
    updateTextTexture();
}
void Text::updateTextTexture() {
    if(!m_pText->getFont()){
        auto font = new sf::Font();
        if(!font->loadFromFile(getDefaultFontPath())){
            LOG_ERROR("Did not load font!");
        }
        m_pText->setFont(*font);
    }
    sf::FloatRect textRect = m_pText->getLocalBounds();

    sf::RenderTexture renderTexture;
    if (renderTexture.create({static_cast<unsigned>(textRect.width),
                              static_cast<unsigned>(textRect.height)})) {
        // Centering Text
        m_pText->setOrigin({textRect.left + textRect.width / 2.0f,
                            textRect.top + textRect.height / 2.0f});
        m_pText->setPosition({textRect.width / 2, textRect.height / 2});
        renderTexture.clear(sf::Color::Transparent);

        renderTexture.draw(*m_pText);

        renderTexture.display();
        auto texture = new sf::Texture(renderTexture.getTexture());
        setTexture(texture);
    } else {
        LOG_CRITICAL("Background of button did not create!");
    }
}
void Text::setText(const sf::Text& text) {
    m_pText = std::make_unique<sf::Text>(text);
    updateTextTexture();
}
void Text::setText(const std::string& string) {
    m_pText->setString(sf::String::fromUtf8(string.begin(), string.end()));
    updateTextTexture();
}
void Text::setColor(sf::Color color) {
    m_pText->setFillColor(color);
    updateTextTexture();
}
void Text::setFont(const sf::Font& font) {
    m_pText->setFont(font);
    updateTextTexture();
}
void Text::setCharacterSize(unsigned int size) {
    m_pText->setCharacterSize(size);
    updateTextTexture();
}
