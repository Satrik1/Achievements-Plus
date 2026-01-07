#include "CCKeyboardDispatcher.hpp"

#include "../Other/Manager.hpp"

bool ProCCKeyboardDispatcher::dispatchKeyboardMSG(enumKeyCodes p0, bool p1, bool p2) {
    auto ret = CCKeyboardDispatcher::dispatchKeyboardMSG(p0, p1, p2);
    auto& am = Manager::get();

    if (!am.isAchievementCompleted(22)) {
        am.m_lastMovementTime = std::chrono::steady_clock::now();
    }

    return ret;
}
