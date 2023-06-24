

#include "../headers/Game.h"
#include "../headers/Log.h"
#include "../headers/utils.h"

int main(){
    LOG_INFO(getDefaultFontPath());
    Game game;
    game.start();

    return 0;
}