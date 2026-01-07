#pragma once

using namespace geode::prelude;

template <typename T>
T* createPopupx(int id) {
    auto ret = new T(id);
    ret->init();
    ret->autorelease();
    return ret;
}

enum Rarity {
    Normal,
    Special,
    Secret,
    Divine
};

enum Type {
    Demons,
    Deaths,
    Attempts,
    Achievements,
    Other
};

struct Achievement {
    int id;
    std::string_view title;
    std::string_view description;
    Rarity rarity;
    Type type;
    int statAmount;
};

constexpr std::array achievements{
    Achievement{ 1, "Baby Steps", "Complete your first Demon", Rarity::Normal, Type::Demons, 1 },
    Achievement{ 2, "Getting Serious", "Complete 3 Demons", Rarity::Normal, Type::Demons, 3 },
    Achievement{ 3, "Pretty Serious… Kind Of", "Complete 5 Demons", Rarity::Normal, Type::Demons, 10 },
    Achievement{ 4, "Demon Grinder", "Complete 10 Demons", Rarity::Normal, Type::Demons, 10 },
    Achievement{ 5, "Okay I'm Locked In", "Complete 20 Demons", Rarity::Normal, Type::Demons, 50 },
    Achievement{ 6, "You Got Skills!", "Complete a Demon without Practice Mode", Rarity::Normal, Type::Other },
    Achievement{ 7, "Oopsie…", "Die 100 times", Rarity::Normal, Type::Deaths, 100 },
    Achievement{ 8, "It Hurts… Really", "Die 500 times", Rarity::Normal, Type::Deaths, 500 },
    Achievement{ 9, "Statistically Not Okay", "Die 1,000 times", Rarity::Normal, Type::Deaths, 1000 },
    Achievement{ 10, "I'm Tired", "Reach 1,000 attempts total", Rarity::Normal, Type::Attempts, 1000 },
    Achievement{ 11, "Sleepy Eyes", "Play for 60 minutes in one session", Rarity::Normal, Type::Other },
    Achievement{ 12, "Unyey", "Die 50 times on the same level", Rarity::Normal, Type::Other },
    Achievement{ 13, "Impossible Timing", "Die very close to the end of a level", Rarity::Special, Type::Other },
    Achievement{ 14, "I Gotchu", "Beat a Demon after 500+ attempts", Rarity::Special, Type::Other },
    Achievement{ 15, "YEYEYEYEYEYYE!!!", "Beat 3 rated levels in a row without dying", Rarity::Special, Type::Other },
    Achievement{ 16, "Huh…", "Beat a rated level on the first attempt", Rarity::Special, Type::Other },
    Achievement{ 17, "Okay Nvm I Take It Back", "Beat a level right after rage quitting", Rarity::Special, Type::Other },
    Achievement{ 18, "Ew…", "Quit a level within 3 seconds", Rarity::Special, Type::Other },
    Achievement{ 19, "YEY??", "Pause the game 20 times in one session", Rarity::Special, Type::Other },
    Achievement{ 20, "Just Continue Playing Dude", "Die 20 times in under 1 minute", Rarity::Special, Type::Other },
    Achievement{ 21, "Ima Take a Big Bumpy Later", "Die at the same place 25 times in a row", Rarity::Special, Type::Other },
    Achievement{ 22, "TV Noises", "Leave the game open without playing for 5 minutes", Rarity::Special, Type::Other },
    Achievement{ 23, "Don't Ask How", "Die instantly after starting a level", Rarity::Secret, Type::Other },
    Achievement{ 24, "Overthinking", "Restart the level 30 times in a row", Rarity::Secret, Type::Other },
    Achievement{ 25, "No Internet", "Pause the game mid-attempt and wait", Rarity::Secret, Type::Other },
    Achievement{ 26, "Hide and Boo", "Open and close the pause menu rapidly", Rarity::Secret, Type::Other },
    Achievement{ 27, "Silence", "Mute the game while playing", Rarity::Secret, Type::Other },
    Achievement{ 28, "Angel Awaken", "Beat a Demon after failing 5,000+ times total", Rarity::Divine, Type::Other },
    Achievement{ 29, "Moving On", "Beat a level you previously quit many times", Rarity::Divine, Type::Other },
    Achievement{ 30, "I Have a Gaming Chair", "Reach 15% on an Extreme Demon", Rarity::Divine, Type::Other },
    Achievement{ 31, "SATRIK!!!", "Unlock 30 achievements", Rarity::Divine, Type::Achievements, 30 }
};