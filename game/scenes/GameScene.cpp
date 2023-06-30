#include "GameScene.h"

#include <SFML/Graphics.hpp>
#include <fstream>
#include <nlohmann/json.hpp>

#include "../../headers/Context.h"
#include "../../headers/Log.h"
#include "../../headers/templates/Button.h"
#include "../prefabs/Field.h"
#include "../prefabs/ScoreText.h"
#include "../scripts/CheckEnd.h"
#include "Menu.h"

GameScene::GameScene(float width, float height, Context *context, Menu *menu)
    : Scene(width, height, context), m_menu(menu){

    auto background = new GameObject();
    auto renderTexture = sf::RenderTexture();
    renderTexture.create(
        {static_cast<unsigned>(width), static_cast<unsigned>(height)});
    renderTexture.clear(sf::Color({0xE9, 0xD8, 0xA6}));
    renderTexture.display();
    background->setTexture(new sf::Texture(renderTexture.getTexture()));
    background->addComponent(new CheckEnd());
    addObject(background);

    std::ifstream f_player_name_r("../game/game_data/player.json");
    nlohmann::json player_name_j = nlohmann::json::parse(f_player_name_r);
    m_playerName = player_name_j["name"];
    f_player_name_r.close();

    std::string filename = "../game/game_data/player_levels.json";

    std::ifstream f_playerLevels(filename);

    nlohmann::json data;
    if(f_playerLevels){
         data = nlohmann::json::parse(f_playerLevels);
    }

    if(data.empty() || !f_playerLevels){
        LOG_ERROR("Incorrect file!");
        f_playerLevels.close();
        std::ofstream f_playerLevels_w(filename);
        nlohmann::json json;
        json["player"] = m_playerName;
        json["left_level"] = 1;
        json["right_level"] = 1;
        json["strokes_count"] =1;
        data = nlohmann::json::array({json});
        f_playerLevels_w << std::setw(4) << data << std::endl;
    }
    bool create = false;
    for (auto it : data) {
        if(it["player"] == m_playerName){
            m_leftField = new Field(true,it["left_level"] , true);
            addObject(m_leftField);
            m_rightField = new Field(false, it["right_level"],true);
            addObject(m_rightField);
            m_strokesCount = it["strokes_count"];
            create = true;
        }
    }
    if(!create){
        m_leftField = new Field(true,1, true);
        addObject(m_leftField);
        m_rightField = new Field(false, 1,true);
        addObject(m_rightField);
    }
    auto scoreText = new ScoreText();
    scoreText->setPosition({0,720/2-20,2});
    addObject(scoreText);

    auto btnBack = new Button();
    auto backTexture = new sf::Texture();
    backTexture->loadFromFile("../game/sprites/back.png");
    backTexture->setSmooth(true);
    btnBack->setText("");
    btnBack->setBackground(*backTexture);
    btnBack->setPosition({-536, 256, 2});
    btnBack->active = true;
    btnBack->setMouseClickAction(
        [this] {

            nlohmann::json q;

                nlohmann::json data;
                data["player"] = m_playerName;
                data["left_level"] = static_cast<int>(m_leftField->getLevel());
                data["right_level"] = static_cast<int>(m_rightField->getLevel());
                data["strokes_count"] = static_cast<int>(m_strokesCount);
                q.push_back(data);

            std::ofstream f_playerLevels_w("../game/game_data/player_levels.json");
            f_playerLevels_w << std::setw(4) << q;
            f_playerLevels_w.close();

            auto context = m_pGameContext;
            auto windowData = context->getWindowData();
            m_menu->updateLeaders();
            return dynamic_cast<Window *>(context->getWindow())->setCurrentScene(m_menu);

        });
    btnBack->setMouseOverAction([btnBack] {
        btnBack->setScale({1.02f, 1.02f, 1.02f});
    });
    btnBack->setMouseOutAction([btnBack] {
        btnBack->setScale({1.f, 1.f, 1.f});
    });
    addObject(btnBack);
}

