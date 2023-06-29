#include "Field.h"

#include <SFML/Graphics.hpp>
#include <fstream>
#include <nlohmann/json.hpp>

#include "../../headers/Log.h"
#include "Ball.h"
#include "Hole.h"
#include "Wall.h"

#define SCALE 30

enum UserData{
    BALL = 5,
    WALL = 6
};

Field::Field(bool isLeft, uint level, bool isPlay): m_level(level), m_left(isLeft), m_play(isPlay) {
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
    m_world.SetContactListener(&m_contactListener);
}
void Field::setLevel(uint level) {
    m_level = level;
    for(auto it: m_walls){
        if(it){
            m_world.DestroyBody(it->m_body);
            it->destroy();
        }
    }
    m_walls.clear();
    if(m_pBall) {
        m_world.DestroyBody(m_pBall->m_body);
        m_pBall->destroy();
        m_pBall = nullptr;
    }
    if(m_pHole) {
        m_pHole->destroy();
        m_pHole = nullptr;
    }
    loadFromFile();

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
        filename.erase(filename.end() - static_cast<int>(std::to_string(m_level).size()) - 5, filename.end());
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
    glm::vec3 ballPos = glm::vec3(data["start_ball_pos"][0], data["start_ball_pos"][1], 0);
    ballPos = localToWorldPosition(ballPos);

    glm::vec3 holePos = glm::vec3(data["hole_pos"][0], data["hole_pos"][1], 0);
    holePos = localToWorldPosition(holePos);

    for (auto wall : data["walls"]) {
        auto gm_wall = new Wall(wall["group"], wall["number"]);
        glm::vec2 wallPos(wall["pos"][0], wall["pos"][1]);
        gm_wall->setLocalPosition(wallPos, this);
        gm_wall->setRotation({0,0, wall["rotation"]});
        m_walls.push_back(gm_wall);
        m_pScene->addObject(gm_wall);

        //box 2d
        auto box = new b2PolygonShape();
        auto pos = gm_wall->getPosition();
        box->SetAsBox(16./SCALE, 16./SCALE);

        auto bodyDef = new b2BodyDef();
        bodyDef->type = b2_staticBody;
        bodyDef->position.Set(pos.x/SCALE,pos.y/SCALE);

        auto fixDef = new b2FixtureDef();
        fixDef->shape = box;
        fixDef->friction = .0f;

        fixDef->restitution = 1.f;

        b2Body* body = m_world.CreateBody(bodyDef);
        body->CreateFixture(fixDef);
        gm_wall->m_body = body;
        b2BodyUserData &userData = body->GetUserData();
        userData.pointer = (uintptr_t)gm_wall;
    }

    m_pBall = new Ball();
    m_pBall->setPosition(ballPos);
    m_pScene->addObject(m_pBall);
    if(m_play){
        m_pBall->player = true;
    }

    //box 2d
    auto circle = new b2CircleShape();
    auto pos = m_pBall->getPosition();
    circle->m_radius = 7./SCALE;

    auto bodyDef = new b2BodyDef();
    bodyDef->type = b2_dynamicBody;
    bodyDef->position.Set(pos.x/SCALE,pos.y/SCALE);

    auto fixDef = new b2FixtureDef();
    fixDef->shape = circle;
    fixDef->friction = .0f;
    fixDef->density = .05f;
    fixDef->restitution = 1;

    b2Body* body = m_world.CreateBody(bodyDef);
    body->CreateFixture(fixDef);
    body->SetLinearDamping(0.6f);
    m_pBall->m_body = body;

    b2BodyUserData &userData = body->GetUserData();
    userData.pointer = (uintptr_t)m_pBall;
    //

    m_pHole = new Hole();
    m_pHole->setPosition(holePos + glm::vec3(0,0,-0.5f));
    m_pScene->addObject(m_pHole);


}
glm::vec3 Field::localToWorldPosition(glm::vec2 pos) {
    auto fieldSize_u = getTexture()->getSize();
    glm::vec2 wallSize(32,32);

    glm::vec2 fieldSize(static_cast<float>(fieldSize_u.x), static_cast<float>(fieldSize_u.y));

    glm::vec3 newPos =
        glm::vec3(pos, 1) * glm::vec3(wallSize.x, -wallSize.y, 1) +
        glm::vec3(wallSize.x / 2, -wallSize.y / 2, 0) + getPosition()
        + glm::vec3(-fieldSize.x/2, fieldSize.y/2,0.1f);
    return newPos;
}
void Field::fixedUpdate() {
    GameObject::fixedUpdate();
    m_world.Step(0.02f, 15,10);
    if(m_pHole != nullptr && m_pBall != nullptr){
        if(glm::distance(m_pHole->getPosition(), m_pBall->getPosition()) <= 5){
            setLevel(m_level + 1);
        }
        if(neededReload){
            neededReload = false;
            std::string filename = "../game/levels/";

            if(m_left){
                filename += "left/";
            }
            else{
                filename += "right/";
            }
            filename += std::to_string(m_level) + ".json";
            std::ifstream f(filename);

            nlohmann::json data = nlohmann::json::parse(f);
            if(data.empty()){
                LOG_ERROR("Incorrect file!");
                return ;
            }

            glm::vec3 ballPos = glm::vec3(data["start_ball_pos"][0], data["start_ball_pos"][1], 0);
            ballPos = localToWorldPosition(ballPos);
            m_pBall->m_body->SetLinearVelocity({0,0});
            m_pBall->setPosition(ballPos);
            m_pBall->m_body->SetTransform({ballPos.x/SCALE,ballPos.y/SCALE}, 0);
        }
    }
}

void Field::ContactListener::BeginContact(b2Contact* contact) {
    if(contact->IsTouching()){
        auto fix1 = contact->GetFixtureA();
        auto fix2 = contact->GetFixtureB();
        auto &userData1 = fix1->GetBody()->GetUserData();
        auto &userData2 = fix2->GetBody()->GetUserData();
        auto *gm1 = reinterpret_cast<GameObject *>(userData1.pointer);
        auto *gm2 = reinterpret_cast<GameObject *>(userData2.pointer);
        if(typeid(*gm2) == typeid(Ball)){
            if(dynamic_cast<Wall *>(gm1)->getGroup() == 11){
                m_field->reload();
            }
        }
        if(typeid(*gm2) == typeid(Wall)){
            if(dynamic_cast<Wall *>(gm2)->getGroup() == 11){
                m_field->reload();
            }
        }
    }
}
void Field::ContactListener::EndContact(b2Contact* contact) {
    b2ContactListener::EndContact(contact);
}
