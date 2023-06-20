#include <utility>

#include "../headers/Context.h"
void Context::setWindowsData(Context::WindowData win_data) {
    m_mainWidowData = std::move(win_data);
}
