#include "../headers/GameObject.h"

#include <SFML/Graphics.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/matrix_decompose.hpp>

#include "../headers/Component.h"
#include "../headers/Log.h"
#include "../headers/Context.h"

sf::Texture *GameObject::getTexture() { return m_texture; }

glm::mat4 GameObject::getTransform() {
    std::unique_lock<std::mutex> lock(m_transform_mutex);
    return m_transform;
}

void GameObject::start() {
    std::unique_lock<std::mutex> lock(m_components_mutex);
    std::for_each(m_components.begin(), m_components.end(), [](Component *component){
       component->start();
    });
}

void GameObject::update() {
    if(!active) return;
    std::unique_lock<std::mutex> lock(m_components_mutex);
    std::for_each(m_components.begin(), m_components.end(), [](Component *component){
        component->update();
    });
}

void GameObject::fixedUpdate() {
    if(!active) return;
    std::unique_lock<std::mutex> lock(m_components_mutex);
    std::for_each(m_components.begin(), m_components.end(), [](Component *component){
        component->fixedUpdate();
    });
}

void GameObject::setTexture(sf::Texture *texture) {
    std::unique_lock<std::mutex> lock(m_texture_mutex);
    m_texture = texture;
}

Context *GameObject::getContext() const {
    return m_pScene->getContext();
}

void GameObject::destroy() {
    std::thread thread([this](){
        {
            std::unique_lock<std::mutex> lock(m_components_mutex);
            m_components.clear();
        }
        m_pScene->destroyGameObject(this);
    });
    thread.detach();
}

void GameObject::addComponent(Component *component) {
    std::thread thread([this, component](){
        std::unique_lock<std::mutex> lock(m_components_mutex);
        component->gameObject = this;
        m_components.push_back(component);
    });
    thread.detach();
}

[[maybe_unused]] void GameObject::setTexture(std::string filename) {
    auto *texture = new sf::Texture();
    if (texture->loadFromFile(filename)) {
        m_texture_mutex.lock();
        delete m_texture;
        m_texture = texture;
        m_texture->setSmooth(true);
        m_texture_mutex.unlock();
        LOG_INFO("Texture from file \"{0}\" loaded", filename);
        return;
    }
    LOG_ERROR("Texture from file \"{0}\" wasn't loaded", filename);
}
void GameObject::setPosition(glm::vec3 position) {
    std::unique_lock<std::mutex> lock(m_transform_mutex);
    m_transform[3][0] = position.x;
    m_transform[3][1] = position.y;
    m_transform[3][2] = position.z;
    m_position = position;
}
void GameObject::setRotation(glm::vec3 rotation) {
    std::unique_lock<std::mutex> lock(m_transform_mutex);
    glm::mat4 rotationMatrix(1.0f);
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.x),
                                 glm::vec3(1.0f, 0.0f, 0.0f));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.y),
                                 glm::vec3(0.0f, 1.0f, 0.0f));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.z),
                                 glm::vec3(0.0f, 0.0f, 1.0f));
    m_rotation = rotation;
    m_transform = glm::translate(glm::mat4(1), m_position) * rotationMatrix * glm::scale(glm::mat4(1), m_scale);
}

[[maybe_unused]] void GameObject::setScale(glm::vec3 scale) {
    std::unique_lock<std::mutex> lock(m_transform_mutex);
    m_transform = glm::scale(m_transform, (1.f/m_scale) * scale);
    m_scale = scale;
}
glm::vec3 GameObject::getPosition() {
    std::unique_lock<std::mutex> lock(m_transform_mutex);
    return m_position;
}
[[maybe_unused]] glm::vec3 GameObject::getRotation() {
    std::unique_lock<std::mutex> lock(m_transform_mutex);
    return m_rotation;
}
[[maybe_unused]] glm::vec3 GameObject::getScale() {
    std::unique_lock<std::mutex> lock(m_transform_mutex);
    return m_scale;
}
[[maybe_unused]] void GameObject::setTransform(glm::mat4 transform) {
    std::unique_lock<std::mutex> lock(m_transform_mutex);
    m_transform = transform;
    glm::quat rotation;
    glm::vec3 skew;
    glm::vec4 perspective;
    glm::decompose(transform, m_scale, rotation, m_position, skew, perspective);
    m_rotation = glm::degrees(glm::eulerAngles(rotation));
}
