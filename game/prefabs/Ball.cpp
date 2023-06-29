#include "Ball.h"

#include <SFML/Graphics.hpp>
#include <random>

#include "../../headers/Log.h"

#define SCALE 30

Ball::Ball() {
    auto texture = new sf::Texture();
    if(!texture->loadFromFile("../game/sprites/ball.png")){
        LOG_ERROR("Texture ball did not load!");
    }
    setTexture(texture);
}
void Ball::fixedUpdate() {
    GameObject::fixedUpdate();

    auto pos = m_body->GetPosition();

    setPosition({pos.x*SCALE, pos.y*SCALE, getPosition().z});
    if(!player){
        if(m_body->GetLinearVelocity().LengthSquared() <= 0.2f){
            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_real_distribution<float> dist(2,18);
            m_body->SetLinearVelocity({dist(rng), dist(rng)});
        }
    }
}
