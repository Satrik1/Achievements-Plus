#include "AchievementPopup.hpp"

class DivinePopup : public AchievementPopup {

private:

    CCLayerColor* m_overlay = nullptr;
    CCSprite* m_gradient1 = nullptr;
    CCSprite* m_gradient2 = nullptr;
    CCSprite* m_whiteBadge = nullptr;
    CCSprite* m_shine1 = nullptr;
    CCSprite* m_shine2 = nullptr;
    CCSprite* m_shine3 = nullptr;
    CCSprite* m_shine4 = nullptr;
    CCSprite* m_shine5 = nullptr;
    CCSprite* m_shine6 = nullptr;
    CCSprite* m_shine7 = nullptr;
    CCParticleSystemQuad* m_particle1 = nullptr;
    CCParticleSystemQuad* m_particle2 = nullptr;
    CCParticleSystemQuad* m_particle3 = nullptr;
    CCParticleSystemQuad* m_particle4 = nullptr;
    CCParticleSystemQuad* m_particle5 = nullptr;

    void spawnParticle(const CCPoint&);

public:

    DivinePopup(int id) : AchievementPopup(id) {}

    bool init() override;

    void show() override;

};