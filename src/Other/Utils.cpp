#include "Utils.hpp"
#include "Manager.hpp"

#include "../UI/NormalPopup.hpp"
#include "../UI/SpecialPopup.hpp"
#include "../UI/SecretPopup.hpp"
#include "../UI/DivinePopup.hpp"

#include <random>

int Utils::getRandomInt(int min, int max) {
    static std::mt19937 gen(std::random_device{}());

    std::uniform_int_distribution<> dis(min, max);
    
    return dis(gen);
}

AchievementPopup* Utils::createPopup(int id) {
    switch (Manager::get().getAchievementById(id).rarity) {
        default:
        case Rarity::Normal: return createPopupx<NormalPopup>(id);
        case Rarity::Special: return createPopupx<SpecialPopup>(id);
        case Rarity::Secret: return createPopupx<SecretPopup>(id);
        case Rarity::Divine: return createPopupx<DivinePopup>(id);
    }
}

float Utils::getPopupDuration(Rarity rarity) {
    switch (rarity) {
        default:
        case Rarity::Normal: return 2.1f;
        case Rarity::Special: return 2.4f;
        case Rarity::Secret: return 3.f;
        case Rarity::Divine: return 4.1f;
    }
}

std::string Utils::getBadgeFilename(Rarity rarity) {
    switch (rarity) {
        default:
        case Rarity::Normal: return "normal-badge.png"_spr;
        case Rarity::Special: return "special-badge.png"_spr;
        case Rarity::Secret: return "secret-badge.png"_spr;
        case Rarity::Divine: return "divine-badge.png"_spr;
    }
}

std::filesystem::path Utils::getSoundPath(Rarity rarity) {
    switch (rarity) {
        default:
        case Rarity::Normal: return dirs::getResourcesDir() / "achievement_01.ogg";
        case Rarity::Special: return Mod::get()->getResourcesDir() / "special.mp3";
        case Rarity::Secret: return Mod::get()->getResourcesDir() / "secret.mp3";
        case Rarity::Divine: return Mod::get()->getResourcesDir() / "divine.mp3";
    }
}

float Utils::getSoundVolume(Rarity rarity) {
    switch (rarity) {
        default:
        case Rarity::Normal: return 1.f;
        case Rarity::Special: return 0.5f;
        case Rarity::Secret: return 0.22f;
        case Rarity::Divine: return 0.3f;
    }
}

float Utils::getSoundPitch(Rarity rarity) {
    switch (rarity) {
        default:
        case Rarity::Normal: return 1.1f;
        case Rarity::Special: return 1.f;
        case Rarity::Secret: return 1.f;
        case Rarity::Divine: return 1.f;
    }
}

float Utils::getBadgeScale(Rarity rarity) {
    switch (rarity) {
        case Rarity::Normal: return 0.85f;
        case Rarity::Special: return 0.872f;
        case Rarity::Secret: return 1.0551f;
        case Rarity::Divine:
        default: return 1.f;
    }
}

std::string Utils::getRarityName(Rarity rarity) {
    switch (rarity) {
        default:
        case Rarity::Normal: return "normal";
        case Rarity::Special: return "special";
        case Rarity::Secret: return "secret";
        case Rarity::Divine: return "divine";
    }
}

std::vector<ccColor3B> Utils::getLabelColors(Rarity rarity) {
    switch (rarity) {
        default:
        case Rarity::Normal: return { ccc3(213, 255, 211), ccc3(151, 255, 146) };
        case Rarity::Special: return { ccc3(255, 77, 125), ccc3(227, 152, 255), ccc3(156, 129, 255), ccc3(169, 226, 250), ccc3(98, 252, 255) };
        case Rarity::Secret: return { ccc3(165, 165, 165), ccc3(116, 116, 116), ccc3(180, 64, 64) };
        case Rarity::Divine: return { ccc3(255, 251, 225), ccc3(255, 254, 180), ccc3(255, 237, 98) };
    }
}

std::vector<ccColor3B> Utils::getTagLabelColors(Rarity rarity) {
    switch (rarity) {
        default:
        case Rarity::Normal: return { ccc3(79, 255, 70), ccc3(186, 255, 183),ccc3(55, 162, 50) };
        case Rarity::Special: return { ccc3(255, 131, 131), ccc3(255, 192, 129), ccc3(255, 255, 125), ccc3(138, 255, 138), ccc3(146, 146, 255), ccc3(255, 133, 231), ccc3(220, 138, 255) };
        case Rarity::Secret: return { ccc3(106, 0, 0), ccc3(255, 130, 130), ccc3(100, 19, 19) };
        case Rarity::Divine: return { ccc3(251, 232, 105), ccc3(255, 254, 180), ccc3(255, 237, 98) };
    }
}

ccColor3B Utils::interpolateColor(const ccColor3B& color1, const ccColor3B& color2, float t) {
    ccColor3B ret;

    ret.r = color1.r + t * (color2.r - color1.r);
    ret.g = color1.g + t * (color2.g - color1.g);
    ret.b = color1.b + t * (color2.b - color1.b);

    return ret;
}

void Utils::colorLabel(CCLabelBMFont* label, const std::vector<ccColor3B>& labelColors) {
    std::vector<CCFontSprite*> children;

    for (const auto& child : label->getChildrenExt<CCFontSprite*>()) {
        if (child->getContentWidth() > 0.f) {
            children.push_back(child);
        }
    }

    if (!labelColors.empty()) {
        auto interval = static_cast<int>(children.size()) / (static_cast<int>(labelColors.size()) - 1);
        auto current = 0;
        auto counter = 0;

        for (int i = 0; i < children.size(); i++) {
            if (counter >= interval) {
                current++;

                if (current >= labelColors.size() - 1) {
                    current = labelColors.size() - 2;
                } else {
                    counter = 0;
                }
            }

            if (children[i]->getContentSize().width <= 0.f) {
                continue;
            }

            counter++;
            
            children[i]->setColor(
                interpolateColor(
                    labelColors[current],
                    labelColors[current + 1],
                    std::min(counter / static_cast<float>(interval), 1.f)
                )
            );
        }
    }
}

void Utils::setHookEnabled(const std::string& name, bool enabled) {
    for (Hook* hook : Mod::get()->getHooks()) {
        if (hook->getDisplayName() == name) {
            (void)(enabled ? hook->enable() : hook->disable());
            break;
        }
    }
}

std::string Utils::getTimeString(int id) {
    auto& am = Manager::get();

    if (!am.achievementHasCompletionDate(id)) {
        return "N/A";
    }

    auto now = std::chrono::system_clock::now();
    auto nowSeconds = std::chrono::duration_cast<std::chrono::seconds>(
        now.time_since_epoch()
    ).count();
    auto diff = nowSeconds - am.m_completedAchievementDates.at(id);
    auto format = [](std::int64_t value, const std::string& unit) {
        return std::to_string(value) + " " + unit +
               (value == 1 ? "" : "s") + " ago";
    };

    if (diff < 60)
        return format(diff, "second");

    if (diff < 3600)
        return format(diff / 60, "minute");

    if (diff < 86400)
        return format(diff / 3600, "hour");

    if (diff < 604800)
        return format(diff / 86400, "day");

    return format(diff / 604800, "week");
}