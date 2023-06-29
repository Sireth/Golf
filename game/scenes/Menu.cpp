#include "Menu.h"

#include <fstream>
#include <nlohmann/json.hpp>

#include "../../headers/Context.h"
#include "../../headers/Log.h"
#include "../../headers/templates/Button.h"
#include "../../headers/templates/Text.h"
#include "../../headers/utils.h"
#include "../prefabs/Field.h"
#include "../scripts/TextInput.h"
#include "GameScene.h"

Menu::Menu(float width, float height, Context *context)
    : Scene(width, height, context) {
    auto background = new GameObject();
    auto renderTexture = sf::RenderTexture();
    renderTexture.create(
        {static_cast<unsigned>(width), static_cast<unsigned>(height)});
    renderTexture.clear(sf::Color({0xE9, 0xD8, 0xA6}));
    renderTexture.display();
    background->setTexture(new sf::Texture(renderTexture.getTexture()));
    addObject(background);

    auto btnTexture = sf::Texture();
    btnTexture.setSmooth(true);
    auto fontJost = new sf::Font();
    fontJost->loadFromFile("../game/fonts/Jost-Regular.ttf");
    auto fontComfortaa = new sf::Font();
    fontComfortaa->loadFromFile("../game/fonts/Comfortaa-Regular.ttf");

    auto gameName = new Text("GOLF", 96);
    gameName->setFont(*fontJost);
    gameName->setColor(sf::Color::Black);
    gameName->setPosition({0, 280, 2});
    addObject(gameName);

    std::list<Button *> leaders;
    std::ifstream f("../game/game_data/leaders.json");

    nlohmann::json data = nlohmann::json::parse(f);

    for (int i = 0; i < data.size(); ++i) {
        auto btn = new Button();
        auto leadersTexture = new sf::Texture();
        leadersTexture->loadFromFile("../game/sprites/leaders.png");
        leadersTexture->setSmooth(true);
        std::string name(data[i]["name"]);
        btn->setText(name + "\t\t\t\t" +
                     to_string(data[i]["score"]));
        btn->setTextColor(sf::Color::Black);
        btn->setBackground(*leadersTexture);
        btn->setPosition({0, 117 + i * 10, 2});
        btn->active = false;
        leaders.push_back(btn);
        addObject(btn);
    }

    auto btn1 = new Button();
    btnTexture.loadFromFile("../game/sprites/btn.png");
    btnTexture.setSmooth(true);
    btn1->setText("ПРОДОЛЖИТЬ");
    btn1->setCharacterSize(48);
    btn1->setFont(*fontComfortaa);
    btn1->setTextColor(sf::Color::Black);
    btn1->setPosition({0, 132, 2});
    btn1->setMouseOverAction([btn1] { btn1->setScale({1.02f, 1.02f, 1.02f}); });
    btn1->setMouseOutAction([btn1] { btn1->setScale({1.f, 1.f, 1.f}); });
    btn1->setMouseClickAction(
        [this] {
            auto context = m_pGameContext;
            auto windowData = context->getWindowData();
            return dynamic_cast<Window *>(context->getWindow())->setCurrentScene(new GameScene(static_cast<float>(windowData.width),static_cast<float>(windowData.height), context));
        });
    addObject(btn1);

    auto btn3 = new Button();
    auto playerName = new GameObject();
    auto playerText = new Text("#", 40);
    auto btnBack = new Button();

    auto btn2 = new Button();
    btn1->setBackground(btnTexture);
    btnTexture.setSmooth(true);
    btn2->setText("ЗАДАТЬ ИГРОКА");
    btn2->setCharacterSize(48);
    btn2->setFont(*fontComfortaa);
    btn2->setTextColor(sf::Color::Black);
    btn2->setBackground(btnTexture);
    btn2->setPosition({0, 7, 2});
    btn2->setMouseOverAction([btn2] { btn2->setScale({1.02f, 1.02f, 1.02f}); });
    btn2->setMouseOutAction([btn2] { btn2->setScale({1.f, 1.f, 1.f}); });
    btn2->setMouseClickAction(
        [btn1, btn2, btn3, playerName, playerText, btnBack] {
            btn1->active = false;
            btn2->active = false;
            btn3->active = false;
            playerName->active = true;
            playerText->active = true;
            btnBack->active = true;
        });
    addObject(btn2);

    btnTexture.setSmooth(true);
    btn3->setText("ЛИДЕРЫ");
    btn3->setCharacterSize(48);
    btn3->setFont(*fontComfortaa);
    btn3->setTextColor(sf::Color::Black);
    btn3->setBackground(btnTexture);
    btn3->setPosition({0, -118, 2});
    btn3->setMouseOverAction([btn3] { btn3->setScale({1.02f, 1.02f, 1.02f}); });
    btn3->setMouseOutAction([btn3] { btn3->setScale({1.f, 1.f, 1.f}); });
    btn3->setMouseClickAction(
        [btn1, btn2, btn3, btnBack, leaders] {
            btn1->active = false;
            btn2->active = false;
            btn3->active = false;
            btnBack->active = true;
            for (auto it : leaders) {
                it->active = true;
            }
        });
    addObject(btn3);

    playerName->setTexture("../game/sprites/player_name.png");
    playerName->active = false;
    playerName->setPosition({0, 0, 1.9});
    addObject(playerName);

    auto backTexture = new sf::Texture();
    backTexture->loadFromFile("../game/sprites/back.png");
    backTexture->setSmooth(true);
    btnBack->setText("");
    btnBack->setBackground(*backTexture);
    btnBack->setPosition({-536, 256, 2});
    btnBack->active = false;
    btnBack->setMouseClickAction(
        [this, btn1, btn2, btn3, playerName, playerText, btnBack, leaders] {
            btn1->active = true;
            btn2->active = true;
            btn3->active = true;
            btnBack->active = false;
            playerName->active = false;
            playerText->active = false;
            for (auto it : leaders) {
                it->active = false;
            }
        });
    btnBack->setMouseOverAction([btnBack] {
        btnBack->setScale({1.02f, 1.02f, 1.02f});
    });
    btnBack->setMouseOutAction([btnBack] {
        btnBack->setScale({1.f, 1.f, 1.f});
    });
    addObject(btnBack);

    playerText->setFont(*fontJost);
    playerText->setColor(sf::Color::Black);
    playerText->setPosition({0, 0, 2});
    playerText->active = false;
    playerText->addComponent(
        new TextInput([this, btn1, btn2, btn3, playerName, playerText,
                       btnBack](const std::string &string) {
            m_playerName = string;
            btn1->active = true;
            btn2->active = true;
            btn3->active = true;
            btnBack->active = false;
            playerName->active = false;
            playerText->active = false;
            nlohmann::json json;
            json["name"] = string;
            std::ofstream o("../game/game_data/player.json");
            o << std::setw(4) << json << std::endl;
        }));
    addObject(playerText);

    auto leftField = new Field(true, 1);
    addObject(leftField);
    auto rightField = new Field(false, 1);
    addObject(rightField);
}
