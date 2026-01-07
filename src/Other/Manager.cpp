#include "Manager.hpp"
#include "Utils.hpp"

#include "../UI/AchievementPopup.hpp"
#include "../UI/AchievementList.hpp"

$on_mod(Loaded) {
    Manager::get().load();
    Utils::setHookEnabled("cocos2d::CCScene::getHighestChildZ", false);
}

Manager& Manager::get() {
    static Manager instance;
    return instance;
}

const Achievement& Manager::getAchievementById(int id) {
    for (const auto& achievement : achievements) {
        if (achievement.id == id) {
            return achievement;
        }
    }

    return achievements[0];
}

bool Manager::isAchievementCompleted(int id) {
    return m_completedAchievements.contains(id);
}

bool Manager::achievementHasCompletionDate(int id) {
    return m_completedAchievements.contains(id)
        && m_completedAchievementDates.contains(id);
}

void Manager::load() {
    m_completedAchievements.clear();
    m_deathsForLevel.clear();
    m_deaths = Mod::get()->getSavedValue<int>("deaths");

    auto obj = Mod::get()->getSavedValue<matjson::Value>("completed-achievements");

    if (obj.isArray()) {
        for (const auto& v : obj) {
            m_completedAchievements.insert(v.asInt().unwrapOr(0));
        }
    }

    obj = Mod::get()->getSavedValue<matjson::Value>("completed-achievement-dates");

    for (const auto& [key, v] : obj) {
        auto date = v.asInt().unwrapOr(0);
        
        if (date > 0) {
            m_completedAchievementDates[numFromString<int>(key).unwrapOr(0)] = date;
        }
    }

    obj = Mod::get()->getSavedValue<matjson::Value>("deaths-for-level");

    for (const auto& v : obj) {
        m_deathsForLevel[numFromString<int>(v.getKey().value_or("0")).unwrapOr(0)] = v.asInt().unwrapOr(0);
    }
}

void Manager::save() {
    Mod::get()->setSavedValue("deaths", m_deaths);

    auto obj = matjson::Value::array();

    for (const auto& achievement : achievements) {
        if (isAchievementCompleted(achievement.id)) {
            obj.push(achievement.id);
        }
    }

    Mod::get()->setSavedValue("completed-achievements", obj);

    obj = matjson::Value{};

    for (const auto& achievement : achievements) {
        if (
            isAchievementCompleted(achievement.id)
            && m_completedAchievementDates.contains(achievement.id)
        ) {
            obj[std::to_string(achievement.id)] = m_completedAchievementDates.at(achievement.id);
        }
    }

    Mod::get()->setSavedValue("completed-achievement-dates", obj);

    obj = matjson::Value{};

    for (const auto& [levelId, deaths] : m_deathsForLevel) {
        obj[std::to_string(levelId)] = deaths;
    }

    Mod::get()->setSavedValue("deaths-for-level", obj);
}

void Manager::completeAchievement(int id) {
    if (isAchievementCompleted(id)) {
        return;
    }

    auto now = std::chrono::system_clock::now();
    auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(
        now.time_since_epoch()
    ).count();

    m_completedAchievements.insert(id);
    m_completedAchievementDates[id] = timestamp;

    checkAchievement(30); // Unlock 30 achievements

    if (m_currentListPopup) {
        m_currentListPopup->update();
    }

    showAchievement(id);
}

void Manager::showAchievement(int id) {
    auto popup = Utils::createPopup(id);
    popup->retain();

    m_queuedPopups.push_back(popup);
    
    if (!m_currentPopup) {
        Manager::nextAchievement();
    }
}

void Manager::nextAchievement() {
    if (m_queuedPopups.empty()) {
        return;
    }

    m_queuedPopups.front()->show();
    m_queuedPopups.pop_front();

    if (m_queuedPopups.empty()) {
        return;
    }
}

void Manager::checkAchievements() {
    for (const auto& achievement : achievements) {
        checkAchievement(achievement);
    }
}

void Manager::checkAchievement(int id) {
    checkAchievement(
        getAchievementById(id)
    );
}

void Manager::checkAchievement(const Achievement& achievement) {
    if (
        achievement.type == Type::Other
        || isAchievementCompleted(achievement.id)
    ) {
        return;
    }

    auto gsm = GameStatsManager::get();
    auto amount = 0;

    switch (achievement.type) {
        case Type::Demons: amount = gsm->getStat("5"); break;
        case Type::Deaths: amount = m_deaths; break;
        case Type::Attempts: amount = gsm->getStat("2"); break;
        case Type::Achievements: amount = m_completedAchievements.size(); break;
    }

    if (amount >= achievement.statAmount) {
        completeAchievement(achievement.id);
    }
}