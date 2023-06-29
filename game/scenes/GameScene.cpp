#include "GameScene.h"

#include <fstream>
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

#include "../../headers/Log.h"
#include "../prefabs/Field.h"

GameScene::GameScene(float width, float height, Context *context)
    : Scene(width, height, context){

    auto background = new GameObject();
    auto renderTexture = sf::RenderTexture();
    renderTexture.create(
        {static_cast<unsigned>(width), static_cast<unsigned>(height)});
    renderTexture.clear(sf::Color({0xE9, 0xD8, 0xA6}));
    renderTexture.display();
    background->setTexture(new sf::Texture(renderTexture.getTexture()));
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
        data = nlohmann::json::array({json});
        f_playerLevels_w << std::setw(4) << data << std::endl;
    }

    for (auto it : data) {
        if(it["player"] == m_playerName){
            auto leftField = new Field(true,it["left_level"] , true);
            addObject(leftField);
            auto rightField = new Field(false, it["right_level"],true);
            addObject(rightField);
        }
    }
}
