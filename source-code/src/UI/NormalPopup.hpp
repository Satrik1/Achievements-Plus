#include "AchievementPopup.hpp"

class NormalPopup : public AchievementPopup {

private:

    CCSprite* m_greenSmallStar1 = nullptr;
    CCSprite* m_greenSmallStar2 = nullptr;
    CCSprite* m_greenCheckmark = nullptr;
    CCSprite* m_greenBigStar1 = nullptr;
    CCSprite* m_greenBigStar2 = nullptr;

public:

    NormalPopup(int id) : AchievementPopup(id) {}

    bool init() override;

    void show() override;

};