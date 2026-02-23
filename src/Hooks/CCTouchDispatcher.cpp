#include "CCTouchDispatcher.hpp"

#include "../Other/Manager.hpp"

void ProCCTouchDispatcher::touches(CCSet* p0, CCEvent* p1, unsigned int p2) {
    CCTouchDispatcher::touches(p0, p1, p2);

    auto& am = Manager::get();
    
    if (!am.isAchievementCompleted(22)) { // Leave the game open without playing for 5 minutes
        am.m_lastMovementTime = std::chrono::steady_clock::now();
    }
}