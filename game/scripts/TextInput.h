#ifndef GOLF_TEXTINPUT_H
#define GOLF_TEXTINPUT_H

#pragma once

#include <chrono>
#include <functional>
#include <string>

#include "../../headers/Component.h"

class TextInput: public Component{
    std::function<void(const std::string& string)> m_action;

    std::chrono::steady_clock::time_point now;
    uint32_t lastKey;

   public:
    void start() override;
    void update() override;
    void fixedUpdate() override;
    explicit TextInput(std::function<void(const std::string& string)> actionAfterEnter);
};

#endif  // GOLF_TEXTINPUT_H
