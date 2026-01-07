#include "SoundManager.hpp"

void SoundUpdater::updateSound(float dt) {
    auto isPlaying = true;
    auto isPaused = false;

    m_channel->getPaused(&isPaused);

    if (!isPaused) {
        m_totalTime += dt;
    }
    
    m_channel->isPlaying(&isPlaying);
    
    if ((m_channel && !isPlaying) || m_totalTime > m_timeout) {
        stop();
    }
}

void SoundUpdater::pause(bool paused) {
    m_channel->setPaused(paused);
}

void SoundUpdater::stop() {
    m_channel->stop();
    m_sound->release();
    this->release();
    m_channel = nullptr;
    SoundManager::remove(this);
    CCScheduler::get()->unscheduleSelector(schedule_selector(SoundUpdater::updateSound), this);
}

SoundManager& SoundManager::get() {
    static SoundManager instance;
    return instance;
}

SoundUpdater* SoundManager::add(FMOD::Channel* channel, FMOD::Sound* sound, float timeout) {
    SoundUpdater* updater = new SoundUpdater(channel, sound, timeout);
    updater->retain();
    CCScheduler::get()->scheduleSelector(schedule_selector(SoundUpdater::updateSound), updater, 0.2f, kCCRepeatForever, 0, false);
    get().m_sounds.push_back(updater);
    return updater;
}

void SoundManager::play(const std::filesystem::path& path, float volume, float pitch) {
    auto fmod = FMODAudioEngine::get();
    auto system = fmod->m_system;

    FMOD::Sound* sound;
    FMOD::Channel* channel;
    
    system->createSound(utils::string::pathToString(path).c_str(), FMOD_DEFAULT, nullptr, &sound);
    system->playSound(sound, nullptr, false, &channel);

    channel->setVolume(volume * fmod->m_sfxVolume);
    channel->setPitch(pitch);
    
    SoundManager::add(channel, sound);
}

void SoundManager::remove(SoundUpdater* updater) {
    std::vector<SoundUpdater*>& sounds = get().m_sounds;
    sounds.erase(std::remove(sounds.begin(), sounds.end(), updater), sounds.end());
}

void SoundManager::retain(SoundUpdater* sound) {
    if (sound) {
        get().m_retainedSounds.insert(sound);
    }
}

void SoundManager::release(SoundUpdater* sound) {
    if (sound) {
        get().m_retainedSounds.erase(sound);
    }
}

void SoundManager::pause(bool paused) {
    for (SoundUpdater* updater : get().m_sounds) {
        updater->pause(paused);
    }
}

void SoundManager::stop() {
    for (SoundUpdater* updater : get().m_sounds) {
        if (!get().m_retainedSounds.contains(updater)) {
            updater->stop();
        }
    }
}