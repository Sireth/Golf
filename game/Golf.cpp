#include "Golf.h"

#include "scenes/Menu.h"
#include "../headers/Context.h"
Golf::Golf(): Game() {
    m_pWindow = std::make_unique<Window>("Golf", 1280, 720, m_pGameContext);
    m_pWindow->setCurrentScene(new Menu(1280, 720, m_pGameContext));
}
