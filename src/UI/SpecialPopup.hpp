#include "AchievementPopup.hpp"

class SpecialPopup : public AchievementPopup {

private:

    CCSprite* m_rainbow1 = nullptr;
    CCSprite* m_rainbow2 = nullptr;
    CCSprite* m_redOrbStar = nullptr;
    CCSprite* m_blueOrbStar = nullptr;

public:

    SpecialPopup(int id) : AchievementPopup(id) {}

    bool init() override;

    void show() override;

};