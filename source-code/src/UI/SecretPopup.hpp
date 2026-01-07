#include "AchievementPopup.hpp"

class SecretPopup : public AchievementPopup {

private:

    CCSprite* m_redStar1 = nullptr;
    CCSprite* m_redStar2 = nullptr;
    CCSprite* m_shine1 = nullptr;
    CCSprite* m_shine2 = nullptr;
    CCSprite* m_shine3 = nullptr;
    CCSprite* m_shine4 = nullptr;
    CCLayerColor* m_layer1 = nullptr;
    CCLayerColor* m_layer2 = nullptr;

public:

    SecretPopup(int id) : AchievementPopup(id) {}

    bool init() override;

    void show() override;

};