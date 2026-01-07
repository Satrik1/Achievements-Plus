#include "../Includes.hpp"

#include <Geode/modify/PlayLayer.hpp>

class $modify(ProPlayLayer, PlayLayer) {

    struct Fields {
        std::deque<std::chrono::steady_clock::time_point> m_deathTimes;

        std::chrono::steady_clock::time_point m_levelOpenTime;
        std::chrono::steady_clock::time_point m_lastDeathTime;

        int m_pauses = 0;
        int m_deathLocationStreak = 0;
        int m_restartStreak = 0;

        bool m_didDie = false;

        CCPoint m_lastDeathLocation = {0, 0};

        ~Fields();
    };

    int getLevelDifficulty();

    void levelComplete();

    void destroyPlayer(PlayerObject*, GameObject*);

    void resetLevel();

    void onQuit();

    void setupHasCompleted();

    void pauseGame(bool);

};