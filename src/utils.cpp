#include "../headers/utils.h"

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>


sf::Transform glmMat4ToSfTransform(const glm::mat4& matrix) {
    sf::Transform transform(matrix[0][0], matrix[1][0], matrix[3][0],
                            matrix[0][1], matrix[1][1], matrix[3][1],
                            matrix[0][3], matrix[1][3], matrix[3][3]);
    return transform;
}
std::string getDefaultFontPath() {
    {
        std::string fontPath;

#if defined(_WIN32) || defined(_WIN64)
        // Windows
        char winFontPath[MAX_PATH];
        GetWindowsDirectory(winFontPath, MAX_PATH);
        fontPath = std::string(winFontPath) + "\\Fonts\\arial.ttf";

#elif defined(__APPLE__) || defined(__MACH__)
        // macOS
        fontPath = "/System/Library/Fonts/Supplemental/Arial.ttf";

#elif defined(__linux__)
        // Linux
        fontPath = "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf";

#else
        // Unsupported OS
        std::cerr << "Unsupported operating system." << std::endl;
        return "";
#endif

        return fontPath;
    }
}
