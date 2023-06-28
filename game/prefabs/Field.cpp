#include "Field.h"

#include <SFML/Graphics.hpp>
#include <fstream>
#include <nlohmann/json.hpp>

#include "../../headers/Log.h"
#include "Wall.h"

Field::Field(bool isLeft, uint level): m_level(level), m_left(isLeft) {
    std::string filename = "../game/sprites/field_";
    if(isLeft){
        filename += "left.png";
    }
    else{
        filename += "right.png";
    }
    setTexture(filename);
    int sizeX = static_cast<int>(getTexture()->getSize().x)/2;
    if(isLeft){
        sizeX = -sizeX;
    }
    setPosition({sizeX,0,0});
}
void Field::start() {
    GameObject::start();
    loadFromFile();
}
void Field::setLevel(uint level) {
    m_level = level;
}
void Field::loadFromFile() {
    std::string filename = "../game/levels/";
    if(m_left){
        filename += "left/";
    }
    else{
        filename += "right/";
    }
    filename += std::to_string(m_level) + ".json";
    std::ifstream f(filename);
    if(!f){
        LOG_ERROR("Indifferent level!");
        filename.erase(filename.begin() - static_cast<int>(std::to_string(m_level).size()) - 5, filename.end());
        m_level = 1;
        filename += std::to_string(m_level) + ".json";
        f.close();
        f = std::ifstream(filename);
    }
    nlohmann::json data = nlohmann::json::parse(f);
    if(data.empty()){
        LOG_ERROR("Incorrect file!");
        return ;
    }
    glm::vec3 ballPos = glm::vec3(data["start_ball_pos"][0], data["start_ball_pos"][1], getPosition().z+ 0.1f);

    for (auto wall : data["walls"]) {
        auto gm_wall = new Wall(wall["group"], wall["number"]);
        glm::vec2 wallPos(wall["pos"][0], wall["pos"][1]);
        gm_wall->setLocalPosition(wallPos, this);
        gm_wall->setRotation({0,0, wall["rotation"]});
        m_walls.push_back(gm_wall);
        m_pScene->addObject(gm_wall);
    }
}
