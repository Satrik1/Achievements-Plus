#include "PlayLayer.hpp"

#include "../Other/Manager.hpp"
#include "../Other/Utils.hpp"

ProPlayLayer::Fields::~Fields() {
    auto& am = Manager::get();

    // Leave the game open without playing for 5 minutes
    if (!am.isAchievementCompleted(22)) {
        Utils::setHookEnabled("cocos2d::CCTouchDispatcher::touches", true);
        Utils::setHookEnabled("cocos2d::CCKeyboardDispatcher::dispatchKeyboardMSG", true);
    }
}

int ProPlayLayer::getLevelDifficulty() {
    int difficulty = 0;

    if (m_level->m_demon > 0) {
        difficulty = m_level->m_demonDifficulty > 0 ? m_level->m_demonDifficulty + 4 : 6;
    } else if (m_level->m_autoLevel) {
        difficulty = -1;
    } else if (m_level->m_ratings < 5) {
        difficulty = 0;
    } else {
        difficulty = m_level->m_ratingsSum / m_level->m_ratings;
    }

    return difficulty;
}

void ProPlayLayer::levelComplete() {
    auto gsm = GameStatsManager::get();
    auto prevStars = gsm->getStat("6");

    PlayLayer::levelComplete();

    auto& am = Manager::get();

    am.checkAchievements();

    auto gotStars = prevStars != gsm->getStat("6");
    auto demon = m_level->m_demon.value() == 1;
    auto levelId = m_level->m_levelID.value();

    if (gotStars && demon) {
        // Complete a Demon without Practice Mode
        if (
            m_level->m_practicePercent <= 0
            && !am.isAchievementCompleted(6)
        ) {
            am.completeAchievement(6);
        }

        // Beat a Demon after 500+ attempts
        if (
            m_level->m_attempts.value() >= 500
            && !am.isAchievementCompleted(14)
        ) {
            am.completeAchievement(14);
        }

        // Beat a Demon after failing 5,000+ times total
        if (
            !am.isAchievementCompleted(28)
            && am.m_deathsForLevel.contains(levelId)
            && am.m_deathsForLevel.at(levelId) >= 5000
        ) {
            am.completeAchievement(28);
        }

        // Reach 15% on an Extreme Demon
        if (
            !am.isAchievementCompleted(30)
            && getLevelDifficulty() == 10
        ) {
            am.completeAchievement(30);
        }
    }

    if (
        gotStars
        && levelId > 0
    ) {
        // Beat 3 rated levels in a row without dying
        if (!am.isAchievementCompleted(15)) {
            am.m_beatenLevels.push_back(levelId);

            if (am.m_beatenLevels.size() >= 3) {
                am.completeAchievement(15);
            }
        }

        // Beat a level you previously quit many times
        if (
            !am.isAchievementCompleted(29)
            && am.m_quitsForLevel.contains(levelId)
            && am.m_quitsForLevel.at(levelId) > 250
        ) {
            am.completeAchievement(29);
        }
    }

    // Beat a rated level on the first attempt
    if (
        gotStars
        && levelId > 0
        && m_level->m_attempts.value() == 1
        && !am.isAchievementCompleted(16)
    ) {
        am.completeAchievement(16);
    }

    // Beat a level right after rage quitting
    if (
        am.m_didRageQuit
        && !am.isAchievementCompleted(17)
    ) {
        am.m_didRageQuit = false;
        am.m_rageQuitAttempt = false;
        am.completeAchievement(17);
    }
}

void ProPlayLayer::destroyPlayer(PlayerObject* player, GameObject* object) {
    if (m_player1->m_isDead) {
        return PlayLayer::destroyPlayer(player, object);
    }

    PlayLayer::destroyPlayer(player, object);

    if (object == m_anticheatSpike || (player != m_player1 && player != m_player2)) {
        return;
    }

    auto levelId = m_level->m_levelID.value();
    auto& am = Manager::get();
    auto f = m_fields.self();

    am.m_deaths++;

    if (levelId > 0) {
        am.m_deathsForLevel[levelId] = am.m_deathsForLevel.contains(levelId)
            ? am.m_deathsForLevel.at(levelId) + 1
            : 0;
    }

    am.checkAchievement(7); // Die 100 times
    am.checkAchievement(8); // Die 500 times
    am.checkAchievement(9); // Die 1,000 times

    // Die 50 times on the same level
    if (
        !am.isAchievementCompleted(12)
        && am.m_deathsForLevel.contains(levelId)
        && am.m_deathsForLevel.at(levelId) >= 50
    ) {
        am.completeAchievement(12);
    }

    // Die very close to the end of a level
    if (
        !m_isPracticeMode
        && !m_isTestMode
        && getCurrentPercentInt() >= 97
        && getCurrentPercentInt() < 100
        && !am.isAchievementCompleted(13)
    ) {
        am.completeAchievement(13);
    }

    // Beat 3 levels in a row without dying
    if (!am.isAchievementCompleted(15)) {
        am.m_beatenLevels.clear();
    }

    // Beat a level right after rage quitting
    if (!am.isAchievementCompleted(17)) {
        m_fields->m_lastDeathTime = std::chrono::steady_clock::now();
        am.m_didRageQuit = false;
    }

    // Die 20 times in under 1 minute
    if (!am.isAchievementCompleted(20)) {
        constexpr auto window = std::chrono::minutes(1);
        auto now = std::chrono::steady_clock::now();

        while (
            !f->m_deathTimes.empty()
            && now - f->m_deathTimes.front() > window
        ) {
            f->m_deathTimes.pop_front();
        }

        f->m_deathTimes.push_back(now);

        if (f->m_deathTimes.size() >= 20) {
            am.completeAchievement(20);
            f->m_deathTimes.clear();
        }
    }

    // Die at the same place 25 times in a row
    if (!am.isAchievementCompleted(21)) {
        auto playerPos = m_player1->getPosition();

        if (
            f->m_lastDeathLocation == ccp(0, 0)
            || ccpDistance(playerPos, f->m_lastDeathLocation) < 50.f
        ) {
            if (++f->m_deathLocationStreak >= 25) {
                am.completeAchievement(21);
            }
        } else {
            f->m_deathLocationStreak = 0;
        }

        f->m_lastDeathLocation = playerPos;
    }

    // Die instantly after starting a level
    if (!am.isAchievementCompleted(23)) {
        auto now = std::chrono::steady_clock::now();
        auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_fields->m_levelOpenTime).count();
        
        if (diff < 1400) {
            am.completeAchievement(23);
        }
    }

    // Restart the level 30 times in a row
    if (!am.isAchievementCompleted(24)) {
        f->m_didDie = true;
    }

    // Reach 15% on an Extreme Demon
    if (
        !am.isAchievementCompleted(30)
        && getCurrentPercentInt() >= 15
        && getLevelDifficulty() == 10
    ) {
        am.completeAchievement(30);
    }
}

void ProPlayLayer::resetLevel() {
    auto gsm = GameStatsManager::get();
    auto prevAttempts = gsm->getStat("2");

    PlayLayer::resetLevel();

    if (prevAttempts == gsm->getStat("2")) {
        return;
    }

    auto& am = Manager::get();

    am.checkAchievement(10); // Reach 1,000 attempts total

    // Beat a level right after rage quitting
    if (!am.isAchievementCompleted(17)) {
        if (
            am.m_didRageQuit
            && !am.m_rageQuitAttempt
        ) {
            am.m_didRageQuit = false;
        }

        am.m_rageQuitAttempt = false;
    }

    // Restart the level 30 times in a row
    if (!am.isAchievementCompleted(24)) {
        auto f = m_fields.self();

        if (f->m_didDie) {
            f->m_restartStreak = 0;
        }

        if (++f->m_restartStreak > 30) {
            am.completeAchievement(24);
        }

        f->m_didDie = false;
    }
}


void ProPlayLayer::onQuit() {
    PlayLayer::onQuit();

    auto& am = Manager::get();
    auto levelId = m_level->m_levelID.value();

    // Beat a level right after rage quitting
    if (levelId > 0 && !am.isAchievementCompleted(17)) {
        auto now = std::chrono::steady_clock::now();
        auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_fields->m_lastDeathTime).count();

        if (diff <= 6070) {
            am.m_rageQuitAttempt = true;
            am.m_didRageQuit = true;
            am.m_rageQuitTime = now;
            am.m_rageQuitId = levelId;
        }
    }

    // Quit a level within 3 seconds
    if (
        !am.isAchievementCompleted(18)
        && !m_levelEndAnimationStarted
    ) {
        auto now = std::chrono::steady_clock::now();
        auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_fields->m_levelOpenTime).count();

        if (diff <= 3000) {
            am.completeAchievement(18);
        }
    }

    // Beat a level you previously quit many times
    if (
        levelId > 0
        && !am.isAchievementCompleted(29)
    ) {
        if (am.m_quitsForLevel.contains(levelId)) {
            am.m_quitsForLevel[levelId] = am.m_quitsForLevel.at(levelId) + 1;
        } else {
            am.m_quitsForLevel[levelId] = 1;
        }
    }
}

void ProPlayLayer::setupHasCompleted() {
    PlayLayer::setupHasCompleted();

    auto& am = Manager::get();
    auto f = m_fields.self();

    // Play for 60 minutes in one session
    if (!am.isAchievementCompleted(11)) {
        auto action = CCRepeatForever::create(
            CCSequence::create(
                CCDelayTime::create(12.f),
                CallFuncExt::create([this] {
                    if (m_gameState.m_totalTime > 3601) {
                        Manager::get().completeAchievement(11);
                        stopActionByTag(124);
                    }
                }),
                nullptr
            )
        );

        action->setTag(124);

        runAction(action);
    }

    // Beat a level right after rage quitting
    if (am.m_didRageQuit && m_level->m_levelID.value() != am.m_rageQuitId) {
        am.m_didRageQuit = false;
        am.m_rageQuitAttempt = false;
    }
    
    if (
        !am.isAchievementCompleted(18) // Quit a level within 3 seconds
        || !am.isAchievementCompleted(23) // Die instantly after starting a level
    ) {
        f->m_levelOpenTime = std::chrono::steady_clock::now();
    }

    // Leave the game open without playing for 5 minutes
    if (!am.isAchievementCompleted(22)) {
        Utils::setHookEnabled("cocos2d::CCTouchDispatcher::touches", false);
        Utils::setHookEnabled("cocos2d::CCKeyboardDispatcher::dispatchKeyboardMSG", false);
    }
}

void ProPlayLayer::pauseGame(bool p0) {
    PlayLayer::pauseGame(p0);

    auto& am = Manager::get();

    // Pause the game 20 times in one session
    if (!am.isAchievementCompleted(19)) {
        if (++m_fields->m_pauses >= 20) {
            am.completeAchievement(19);
        }
    }
}