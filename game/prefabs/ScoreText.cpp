#include "ScoreText.h"

#include "../../headers/Log.h"
#include "../scenes/GameScene.h"

void ScoreText::update() {
    GameObject::update();
    m_score = reinterpret_cast<GameScene *>(m_pScene)->m_score;

    std::string string = "SCORE: " + std::to_string(m_score);

    m_pFont = std::make_unique<sf::Font>();
    m_pFont->loadFromFile("../game/fonts/Comfortaa-Regular.ttf");
    m_pText = std::make_unique<sf::Text>(*m_pFont, string, 40);
    m_pText->setFillColor(sf::Color::Black);

    auto textRect = m_pText->getLocalBounds();

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