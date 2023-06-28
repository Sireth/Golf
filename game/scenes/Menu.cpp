#include "Menu.h"

#include "../../headers/Context.h"
#include "../../headers/Log.h"
#include "../../headers/templates/Button.h"
#include "../../headers/templates/Text.h"
#include "../../headers/utils.h"


Menu::Menu(float width, float height, Context *context): Scene( width, height, context)  {
    auto background = new GameObject();
    auto renderTexture = sf::RenderTexture();
    renderTexture.create({static_cast<unsigned>(width),static_cast<unsigned>(height)});
    renderTexture.clear(sf::Color({0xE9, 0xD8, 0xA6}));
    renderTexture.display();
    background->setTexture(new sf::Texture(renderTexture.getTexture()));
    addObject(background);

    auto btnTexture = sf::Texture();
    btnTexture.setSmooth(true);
    auto fontJost = sf::Font();
    fontJost.loadFromFile("../game/fonts/Jost-Regular.ttf");
    auto fontComfortaa = sf::Font();
    fontComfortaa.loadFromFile("../game/fonts/Comfortaa-Regular.ttf");

    auto gameName = new Text("GOLF", 96);
    gameName->setFont(fontJost);
    gameName->setColor(sf::Color::Black);
    gameName->setPosition({0,296,2});
    addObject(gameName);

    auto btn1 = new Button();
    btnTexture.loadFromFile("../game/sprites/btn.png");
    btnTexture.setSmooth(true);
    btn1->setText("ПРОДОЛЖИТЬ");
    btn1->setCharacterSize(48);
    btn1->setFont(fontComfortaa);
    btn1->setTextColor(sf::Color::Black);
    btn1->setBackground(btnTexture);
    btn1->setPosition({0,132,2});
    btn1->setMouseOverAction([btn1]{btn1->setScale({1.05f, 1.05f,1.05f});});
    btn1->setMouseOutAction([btn1]{btn1->setScale({1.f, 1.f,1.f});});
    addObject(btn1);

    auto btn2 = new Button();
    btnTexture.setSmooth(true);
    btn2->setText("НОВЫЙ ИГРОК");
    btn2->setCharacterSize(48);
    btn2->setFont(fontComfortaa);
    btn2->setTextColor(sf::Color::Black);
    btn2->setBackground(btnTexture);
    btn2->setPosition({0,7,2});
    btn2->setMouseOverAction([btn2]{btn2->setScale({1.05f, 1.05f,1.05f});});
    btn2->setMouseOutAction([btn2]{btn2->setScale({1.f, 1.f,1.f});});
    addObject(btn2);

    auto btn3 = new Button();
    btnTexture.setSmooth(true);
    btn3->setText("ЛИДЕРЫ");
    btn3->setCharacterSize(48);
    btn3->setFont(fontComfortaa);
    btn3->setTextColor(sf::Color::Black);
    btn3->setBackground(btnTexture);
    btn3->setPosition({0,-118,2});
    btn3->setMouseOverAction([btn3]{btn3->setScale({1.05f, 1.05f,1.05f});});
    btn3->setMouseOutAction([btn3]{btn3->setScale({1.f, 1.f,1.f});});
    addObject(btn3);
}
