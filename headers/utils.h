#ifndef PONG_UTILS_H
#define PONG_UTILS_H
#pragma once

#include "glm/glm.hpp"


namespace sf{
    class Transform;
}


sf::Transform glmMat4ToSfTransform(const glm::mat4& matrix);

#endif  // PONG_UTILS_H
