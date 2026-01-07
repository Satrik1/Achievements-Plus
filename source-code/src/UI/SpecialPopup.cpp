#include "SpecialPopup.hpp"

void SpecialPopup::show() {
    AchievementPopup::show();

    m_bg2->stopAllActions();
    m_bg2->runAction(CCEaseInOut::create(CCFadeOut::create(0.39f), 1.8f));

    m_glow->stopAllActions();
    m_glow->runAction(CCSequence::create(
        CCEaseInOut::create(CCFadeTo::create(0.35f, 255), 2.f),
        CCDelayTime::create(0.3f),
        CCEaseInOut::create(CCFadeTo::create(2.3f, 150), 2.f),
        nullptr
    ));

    m_rainbow1->runAction(CCSequence::create(
        CCDelayTime::create(0.25f),
        CCEaseBackOut::create(CCRotateTo::create(0.3f, 90)),
        nullptr
    ));

    m_rainbow2->runAction(CCSequence::create(
        CCDelayTime::create(0.13f),
        CCEaseBackOut::create(CCRotateTo::create(0.3f, -90)),
        nullptr
    ));

    m_redOrbStar->runAction(CCRepeatForever::create(
        CCSequence::create(
            CCEaseSineInOut::create(CCMoveBy::create(0.75f, {0, 0.5f})),
            CCEaseSineInOut::create(CCMoveBy::create(0.75f, {0, -0.5f})),
            nullptr
        )
    ));

    m_redOrbStar->runAction(CCSequence::create(
            CCDelayTime::create(0.25f),
            CCEaseSineOut::create(CCEaseBackOut::create(CCScaleTo::create(0.55f, 0.75f))),
            CCDelayTime::create(1.72f),
            CCEaseSineOut::create(CCEaseBackIn::create(CCScaleTo::create(0.62f, 0.f))),
            nullptr
    ));

    m_blueOrbStar->runAction(CCRepeatForever::create(
        CCSequence::create(
            CCDelayTime::create(0.2f),
            CCEaseSineInOut::create(CCMoveBy::create(0.75f, {0, 0.5f})),
            CCEaseSineInOut::create(CCMoveBy::create(0.75f, {0, -0.5f})),
            nullptr
        )
    ));

    m_blueOrbStar->runAction(CCSequence::create(
        CCDelayTime::create(0.32f),
        CCEaseSineOut::create(CCEaseBackOut::create(CCScaleTo::create(0.5f, 0.7f))),
        CCDelayTime::create(1.5f),
        CCEaseSineOut::create(CCEaseBackIn::create(CCScaleTo::create(0.75f, 0.f))),
        nullptr
    ));
}

bool SpecialPopup::init() {
    AchievementPopup::init();

    m_glow->setScaleY(4.3f);
    m_glow->setColor({ 255, 117, 232 });
    m_bg2->setColor({ 224, 194, 255 });

    m_rainbow1 = CCSprite::create("rainbow-1.png"_spr);
    m_rainbow1->setScale(0.675f);
    m_rainbow1->setPosition({140, 0});
    m_rainbow1->setAnchorPoint({0.5f, 0.f});
    m_rainbow1->setRotation(-90);
    
    m_layerColor->addChild(m_rainbow1, -1);

    m_rainbow2 = CCSprite::create("rainbow-1.png"_spr);
    m_rainbow2->setScale(0.675f);
    m_rainbow2->setPosition({-140, 0});
    m_rainbow2->setAnchorPoint({0.5f, 0.f});
    m_rainbow2->setRotation(90);
    
    m_layerColor->addChild(m_rainbow2, -1);

    auto rainbow = CCSprite::create("rainbow-2.png"_spr);
    rainbow->setScaleX(0.675f);
    rainbow->setScaleY(2.f);
    rainbow->setPosition({-100, 20});
    rainbow->setAnchorPoint({0.5f, 0.f});
    rainbow->setOpacity(40);
    
    m_layerColor->addChild(rainbow, -1);

    rainbow = CCSprite::create("rainbow-2.png"_spr);
    rainbow->setScaleX(0.675f);
    rainbow->setScaleY(2.f);
    rainbow->setPosition({100, 20});
    rainbow->setAnchorPoint({0.5f, 0.f});
    rainbow->setOpacity(40);
    
    m_layerColor->addChild(rainbow, -1);

    m_redOrbStar = CCSprite::create("red-orb-star.png"_spr);
    m_redOrbStar->setScale(0.f);
    m_redOrbStar->setRotation(340);
    m_redOrbStar->setPosition({-184, -32});

    m_layerColor->addChild(m_redOrbStar);

    m_blueOrbStar = CCSprite::create("blue-orb-star.png"_spr);
    m_blueOrbStar->setScale(0.f);
    m_blueOrbStar->setRotation(19);
    m_blueOrbStar->setPosition({178, 36});

    m_layerColor->addChild(m_blueOrbStar);
    
    return true;
}