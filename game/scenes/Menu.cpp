#include "Menu.h"

#include "../../headers/Context.h"
#include "../../headers/Log.h"
#include "../../headers/templates/Button.h"
#include "../../headers/utils.h"
Menu::Menu(float width, float height, Context *context): Scene( width, height, context)  {
    auto btn1 = new Button(glm::vec2(100,100));

}
