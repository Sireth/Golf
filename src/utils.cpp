#include "../headers/utils.h"

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>


sf::Transform glmMat4ToSfTransform(const glm::mat4& matrix) {
    sf::Transform transform(matrix[0][0], matrix[1][0], matrix[3][0],
                            matrix[0][1], matrix[1][1], matrix[3][1],
                            matrix[0][3], matrix[1][3], matrix[3][3]);
    return transform;
}