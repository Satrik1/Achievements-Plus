#pragma once

#include "../Includes.hpp"

class AchievementPopup;
class AchievementList;

class Manager {

public:

    std::unordered_set<int> m_completedAchievements;
    
    std::unordered_map<int, int64_t> m_completedAchievementDates;
    std::unordered_map<int, int> m_deathsForLevel;
    std::unordered_map<int, int> m_quitsForLevel;

    std::vector<int> m_beatenLevels;

    std::deque<AchievementPopup*> m_queuedPopups;

    std::chrono::steady_clock::time_point m_rageQuitTime;
    std::chrono::steady_clock::time_point m_lastMovementTime;

    AchievementList* m_currentListPopup = nullptr;
    AchievementPopup* m_currentPopup = nullptr;

    int m_deaths = 0;
    int m_rageQuitId;
    int m_wa = 1;

    bool m_firstLoad = true;
    bool m_rageQuitAttempt = false;
    bool m_didRageQuit = false;

    static Manager& get();

    const Achievement& getAchievementById(int);

    bool isAchievementCompleted(int);

    bool achievementHasCompletionDate(int);

    void nextAchievement();

    void load();
    
    void save();

    void completeAchievement(int);

    void showAchievement(int);

    void checkAchievement(int);

    void checkAchievement(const Achievement&);

    void checkAchievements();

};