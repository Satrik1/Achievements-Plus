#include "AchievementPopup.hpp"

#include "../Other/Manager.hpp"
#include "../Other/Utils.hpp"
#include "../Other/SoundManager.hpp"

AchievementPopup::AchievementPopup(int id)
    : m_achievement(Manager::get().getAchievementById(id)) {}

int AchievementPopup::getAchievementId() {
    return m_achievement.id;
}
    
void AchievementPopup::show() {
    Utils::setHookEnabled("cocos2d::CCScene::getHighestChildZ", true);

    SoundManager::play(
        Utils::getSoundPath(m_achievement.rarity),
        Utils::getSoundVolume(m_achievement.rarity),
        Utils::getSoundPitch(m_achievement.rarity)
    );

    auto scene = CCScene::get();
    auto winSize = CCDirector::get()->getWinSize();

    this->setZOrder(scene->getHighestChildZ() + 999);
    scene->addChild(this);

    Manager::get().m_currentPopup = this;
    SceneManager::get()->keepAcrossScenes(this);

    this->setPosition({winSize.width / 2.f, winSize.height + 50});
    m_layerColor->runAction(CCSequence::create(
        CCEaseBounceOut::create(CCMoveBy::create(0.3f, {0, -102})),
        CCDelayTime::create(Utils::getPopupDuration(m_achievement.rarity)),
        CallFuncExt::create([] {
            SoundManager::play(Mod::get()->getResourcesDir() / "achievement-out.ogg", 0.45f, 1.3f);
        }),
        CCEaseSineIn::create(CCMoveBy::create(0.4f, {0, 102})),
        CCDelayTime::create(0.1f),
        CallFuncExt::create([this] {
            auto& am = Manager::get();
            Utils::setHookEnabled("cocos2d::CCScene::getHighestChildZ", false);
            am.m_currentPopup = nullptr;
            am.nextAchievement();
            removeFromParent();
        }),
        nullptr
    ));

    m_glow->runAction(CCSequence::create(
        CCEaseInOut::create(CCFadeTo::create(0.35f, 255), 2.f),
        CCDelayTime::create(0.3f),
        CCEaseInOut::create(CCFadeTo::create(2.3f, 140), 2.f),
        nullptr
    ));

    m_layerColor->runAction(CCEaseInOut::create(CCScaleTo::create(0.4f, 1.f), 2.f));
    m_bg2->runAction(CCEaseInOut::create(CCFadeOut::create(0.32f), 1.8f));
}

bool AchievementPopup::init() {
    CCNodeRGBA::init();

    auto title = std::string(m_achievement.title);
    auto description = std::string(m_achievement.description);

    m_layerColor = CCLayerColor::create({0, 0, 0, 0}, 0, 0);

    addChild(m_layerColor);

    m_glow = CCSprite::createWithSpriteFrameName("achievementGlow_001.png");
    m_glow->setOpacity(0);
    m_glow->setScale(4.f);

    m_layerColor->addChild(m_glow);

    m_bg = CCScale9Sprite::create("GJ_square01.png");
    m_bg->setContentSize({300, 80});

    m_layerColor->addChild(m_bg);

    m_badge = CCSprite::create(Utils::getBadgeFilename(m_achievement.rarity).c_str());
    m_badge->setScale(51.811f / m_badge->getContentSize().width * Utils::getBadgeScale(m_achievement.rarity));
    m_badge->setPosition({-112.08f, 0});

    m_layerColor->addChild(m_badge, 2);

    m_badgeShadow = CCSprite::create(Utils::getBadgeFilename(m_achievement.rarity).c_str());
    m_badgeShadow->setOpacity(78);
    m_badgeShadow->setColor({0, 0, 0});
    m_badgeShadow->setScale(m_badge->getScale());
    m_badgeShadow->setPosition(m_badge->getPosition() + ccp(1.2f, -2));

    m_layerColor->addChild(m_badgeShadow);

    auto titleLabel = CCLabelBMFont::create(title.c_str(), "bigFont.fnt");
    titleLabel->setPosition({-78, 20});
    titleLabel->setAnchorPoint({0, 0.5f});
    titleLabel->setAnchorPoint({0, 0.5f});
    titleLabel->limitLabelWidth(200.f, 0.58f, 0.0001f);

    m_layerColor->addChild(titleLabel, 2);

    auto descriptionLabel = TextArea::create(description.c_str(), "chatFont.fnt", 1.f, 200.f, {0.f, 1.f}, 20.f, false);
    descriptionLabel->setScale(0.95f);
    descriptionLabel->setPositionX(-78);
    descriptionLabel->setAnchorPoint({0, 0.5f});

    m_layerColor->addChild(descriptionLabel, 2);

    m_bg2 = CCScale9Sprite::create("square02b_001.png");
    m_bg2->setOpacity(0);
    m_bg2->setContentSize({300, 80});
    m_bg2->setOpacity(255);

    m_layerColor->addChild(m_bg2, 5);

    Utils::colorLabel(titleLabel, Utils::getLabelColors(m_achievement.rarity));

    return true;
}