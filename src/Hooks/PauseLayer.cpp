#include "PauseLayer.hpp"

#include "../Other/Manager.hpp"

void ProPauseLayer::updateTime(float dt) {
    auto& am = Manager::get();

    if (am.isAchievementCompleted(25)) {
        return;
    }

    auto f = m_fields.self();

    f->m_time += dt;

    // Pause the game mid-attempt and wait
    if (f->m_time >= 600.f) {
        am.completeAchievement(25);
    }
}

void ProPauseLayer::onResume(CCObject* sender) {
    auto& am = Manager::get();

    // Open and close the pause menu rapidly
    if (
        !am.isAchievementCompleted(26)
        && m_fields->m_time < 0.5f
    ) {
        am.completeAchievement(26);
    }
    
    PauseLayer::onResume(sender);
}

void ProPauseLayer::customSetup() {
    PauseLayer::customSetup();

    auto& am = Manager::get();

    if (
        !am.isAchievementCompleted(25) // Pause the game mid-attempt and wait
        || !am.isAchievementCompleted(26) // Open and close the pause menu rapidly
    ) {
        schedule(schedule_selector(ProPauseLayer::updateTime), 0.016f, kCCRepeatForever, 0.016f);
    }

    auto fmod = FMODAudioEngine::get();
    m_fields->m_gameWasUnmuted = fmod->m_sfxVolume > 0.f || fmod->m_musicVolume > 0.f;
}

void ProPauseLayer::checkMute() {
    auto& am = Manager::get();

    if (!PlayLayer::get() || am.isAchievementCompleted(27)) {
        return;
    }

    auto fmod = FMODAudioEngine::get();
    auto f = m_fields.self();

    if (
        f->m_gameWasUnmuted
        && fmod->m_musicVolume <= 0.f
        && fmod->m_sfxVolume <= 0.f
    ) {
        am.completeAchievement(27);
    }
    else if (!f->m_gameWasUnmuted) {
        f->m_gameWasUnmuted = fmod->m_sfxVolume > 0.f || fmod->m_musicVolume > 0.f;
    }
}

void ProPauseLayer::musicSliderChanged(CCObject* sender) {
    PauseLayer::musicSliderChanged(sender);

    checkMute(); // Mute the game while playing
}

void ProPauseLayer::sfxSliderChanged(CCObject* sender) {
    PauseLayer::sfxSliderChanged(sender);

    auto& am = Manager::get();
    
    checkMute(); // Mute the game while playing
}