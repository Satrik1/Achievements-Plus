#include "Includes.hpp"

#include "Other/Manager.hpp"

$on_mod(Loaded) {

    KeyboardInputEvent().listen([](KeyboardInputData& data) {
        auto& am = Manager::get();

        if (!PlayLayer::get() && !am.isAchievementCompleted(22)) { // Leave the game open without playing for 5 minutes
            am.m_lastMovementTime = std::chrono::steady_clock::now();
        }
    }).leak();

}