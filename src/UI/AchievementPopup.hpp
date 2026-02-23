#pragma once

#include "../Includes.hpp"

class AchievementPopup : public CCNodeRGBA {

protected:

    CCLayerColor* m_layerColor = nullptr;

    CCSprite* m_badge = nullptr;
    CCSprite* m_badgeShadow = nullptr;
    CCSprite* m_glow = nullptr;

    NineSlice* m_bg = nullptr;
    NineSlice* m_bg2 = nullptr;

    Achievement m_achievement;

    AchievementPopup(int);

    virtual bool init() override;

public:

    int getAchievementId();

    virtual void show();
};