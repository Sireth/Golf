#ifndef GOLF_UTILS_H
#define GOLF_UTILS_H
#pragma once

#include <glm/glm.hpp>
#include <iostream>
#include <string>


namespace sf{
    class Transform;
}


sf::Transform glmMat4ToSfTransform(const glm::mat4& matrix);



#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#elif defined(__APPLE__) || defined(__MACH__)
#include <TargetConditionals.h>
#if TARGET_OS_MAC
#include <CoreFoundation/CoreFoundation.h>
#endif
#elif defined(__linux__)

#include <unistd.h>
#include <climits>
#endif

std::string getDefaultFontPath();

#endif  // GOLF_UTILS_H
