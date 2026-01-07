#include "NormalPopup.hpp"

void NormalPopup::show() {
    AchievementPopup::show();

    m_greenSmallStar1->runAction(CCSequence::create(
        CCDelayTime::create(0.12f),
        CCSpawn::create(
            CCEaseSineOut::create(CCEaseBackOut::create(CCRotateBy::create(0.7f, -57))),
            CCEaseSineOut::create(CCEaseBackOut::create(CCScaleTo::create(0.7f, 0.74f))),
            nullptr
        ),
        nullptr
    ));

    m_greenSmallStar2->runAction(CCSequence::create(
        CCDelayTime::create(0.22f),
        CCSpawn::create(
            CCEaseSineOut::create(CCEaseBackOut::create(CCRotateBy::create(0.6f, 45))),
            CCEaseSineOut::create(CCEaseBackOut::create(CCScaleTo::create(0.6f, 0.59f))),
            nullptr
        ),
        nullptr
    ));

    m_greenBigStar1->runAction(CCSequence::create(
        CCDelayTime::create(0.12f),
        CCEaseSineOut::create(CCEaseBackOut::create(CCScaleTo::create(0.6f, 0.75f))),
        nullptr
    ));

    m_greenBigStar2->runAction(CCSequence::create(
        CCDelayTime::create(0.18f),
        CCEaseSineOut::create(CCEaseBackOut::create(CCScaleTo::create(0.6f, 0.75f))),
        nullptr
    ));
}

bool NormalPopup::init() {
    AchievementPopup::init();

    m_greenSmallStar1 = CCSprite::create("green-small-star.png"_spr);
    m_greenSmallStar1->setOpacity(245);
    m_greenSmallStar1->setRotation(45);
    m_greenSmallStar1->setScale(0.f);
    m_greenSmallStar1->setPosition({ -148, -36 });

    m_layerColor->addChild(m_greenSmallStar1);

    m_greenSmallStar2 = CCSprite::create("green-small-star.png"_spr);
    m_greenSmallStar2->setOpacity(245);
    m_greenSmallStar2->setRotation(-20);
    m_greenSmallStar2->setScale(0.f);
    m_greenSmallStar2->setPosition({ 148, 38 });

    m_layerColor->addChild(m_greenSmallStar2);

    m_greenBigStar1 = CCSprite::create("green-big-star.png"_spr);
    m_greenBigStar1->setPosition({169, -24});
    m_greenBigStar1->setRotation(11);
    m_greenBigStar1->setScale(0.f);
    
    m_layerColor->addChild(m_greenBigStar1);

    m_greenBigStar2 = CCSprite::create("green-big-star.png"_spr);
    m_greenBigStar2->setPosition({-169, 26});
    m_greenBigStar2->setRotation(-15);
    m_greenBigStar2->setScale(0.f);
    
    m_layerColor->addChild(m_greenBigStar2);

    return true;
}