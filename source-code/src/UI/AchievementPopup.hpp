#pragma once

#include "../Includes.hpp"

class AchievementPopup : public CCNodeRGBA {

protected:

    CCLayerColor* m_layerColor = nullptr;

    CCSprite* m_badge = nullptr;
    CCSprite* m_badgeShadow = nullptr;
    CCSprite* m_glow = nullptr;

    CCScale9Sprite* m_bg = nullptr;
    CCScale9Sprite* m_bg2 = nullptr;

    Achievement m_achievement;

    AchievementPopup(int);

    virtual bool init() override;

private:

    void setupNormal();
    void setupSpecial();
    void setupSecret();
    void setupDivine();

    void showNormal();
    void showSpecial();
    void showSecret();
    void showDivine();

public:

    int getAchievementId();

    virtual void show();
};