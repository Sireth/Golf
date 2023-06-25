

#include "../game/Golf.h"
#include "../headers/Log.h"
#include "../headers/utils.h"

int main(){
    LOG_INFO(getDefaultFontPath());
    Golf game;
    game.start();

    return 0;
}