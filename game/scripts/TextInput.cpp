#include "TextInput.h"

#include <utility>

#include "../../headers/Context.h"
#include "../../headers/Log.h"
#include "../../headers/GameObject.h"
#include "../../headers/templates/Text.h"

void TextInput::start() {
    now = std::chrono::steady_clock::now();
}
void TextInput::update() {
    auto context = gameObject->m_pScene->getContext();
    auto event = context->getEvent();
    auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - now).count();
    if (event.type == sf::Event::TextEntered && (deltaTime > 150 || event.text.unicode != lastKey)){
        now = std::chrono::steady_clock::now();
        lastKey = event.text.unicode;
        auto text = dynamic_cast<Text *>(gameObject);
        std::string string = text->getString();

        if (event.text.unicode == 8){   // Delete key
            string = string.substr(0, string.size() - 1);
            if(string.size() <= 1){
                string = "#";
            }
        }
        else if(event.text.unicode == '\r'){
            text->setText("#");
            return m_action(string);
        }
        else if (string.size() < 8){
            string += event.text.unicode;
        }
        text->setText(string);
    }
}
void TextInput::fixedUpdate() {}
TextInput::TextInput(std::function<void(const std::string& string)> actionAfterEnter): m_action(std::move(actionAfterEnter)) {}
