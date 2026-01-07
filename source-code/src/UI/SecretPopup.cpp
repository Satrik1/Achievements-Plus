#include "SecretPopup.hpp"

void SecretPopup::show() {
    AchievementPopup::show();

    m_bg2->stopAllActions();
    m_bg2->runAction(CCEaseInOut::create(CCFadeOut::create(0.39f), 1.8f));

    m_glow->stopAllActions();
    m_glow->runAction(CCSequence::create(
        CCEaseInOut::create(CCFadeTo::create(0.35f, 255), 2.f),
        CCDelayTime::create(0.3f),
        CCEaseInOut::create(CCFadeTo::create(2.3f, 200), 2.f),
        nullptr
    ));

    m_layer1->runAction(CCSequence::create(
        CCDelayTime::create(1.3f),
        CCBlink::create(0.3f, 5),
        CCTintTo::create(0.f, 255, 255, 255),
        nullptr
    ));

    m_layer2->runAction(CCSequence::create(
        CCDelayTime::create(1.75f),
        CCBlink::create(0.3f, 5),
        CCTintTo::create(0.f, 255, 255, 255),
        nullptr
    ));

    m_bg->runAction(CCSequence::create(
        CCDelayTime::create(1.3f),
        CCTintTo::create(0.f, 220, 220, 220),
        CCBlink::create(0.3f, 51),
        CCDelayTime::create(0.15f),
        CCTintTo::create(0.f, 220, 220, 220),
        CCBlink::create(0.3f, 51),
        CCTintTo::create(0.f, 255, 255, 255),
        nullptr
    ));

    m_badge->runAction(CCSequence::create(
        CCDelayTime::create(1.75f),
        CCBlink::create(0.3f, 51),
        CCDelayTime::create(0.43f),
        CCBlink::create(0.3f, 51),
        nullptr
    ));

    m_redStar1->runAction(CCSequence::create(
        CCDelayTime::create(0.12f),
        CCSpawn::create(
            CCEaseSineOut::create(CCEaseBackOut::create(CCRotateBy::create(0.7f, -25))),
            CCEaseSineOut::create(CCEaseBackOut::create(CCScaleTo::create(0.7f, 0.85f))),
            nullptr
        ),
        CCDelayTime::create(0.4f),
        CCTintTo::create(0.f, 180, 180, 180),
        CCBlink::create(0.3f, 5),
        CCTintTo::create(0.f, 255, 255, 255),
        CCDelayTime::create(1.5f),
        CCEaseSineOut::create(CCEaseBackIn::create(CCScaleTo::create(0.62f, 0.f))),
        nullptr
    ));

    m_redStar2->runAction(CCSequence::create(
        CCDelayTime::create(0.2f),
        CCSpawn::create(
            CCEaseSineOut::create(CCEaseBackOut::create(CCRotateBy::create(0.7f, 25))),
            CCEaseSineOut::create(CCEaseBackOut::create(CCScaleTo::create(0.7f, 0.85f))),
            nullptr
        ),
        CCDelayTime::create(0.6f),
        CCTintTo::create(0.f, 180, 180, 180),
        CCBlink::create(0.3f, 5),
        CCTintTo::create(0.f, 255, 255, 255),
        CCDelayTime::create(1.3f),
        CCEaseSineOut::create(CCEaseBackIn::create(CCScaleTo::create(0.62f, 0.f))),
        nullptr
    ));

    m_shine1->runAction(
        CCSpawn::create(
            CCSequence::create(
                CCDelayTime::create(0.2f),
                CCEaseSineOut::create(CCEaseBackOut::create(CCScaleTo::create(0.67f, 0.65f))),
                CCDelayTime::create(0.9f),
                CCTintTo::create(0.f, 200, 200, 200),
                CCBlink::create(0.3f, 5),
                CCTintTo::create(0.f, 255, 0, 0),
                CCDelayTime::create(1.f),
                CCEaseSineOut::create(CCEaseBackIn::create(CCScaleTo::create(0.62f, 0.f))),
                nullptr
            ),
            CCSequence::create(
                CCDelayTime::create(0.2f),
                CCEaseIn::create(CCFadeTo::create(0.02f, 255), 2.f),
                CCDelayTime::create(0.2f),
                CCEaseInOut::create(CCTintTo::create(0.35f, 255, 0, 0), 2.f),
                nullptr
            ),
            nullptr
        )
    );

    m_shine2->runAction(
        CCSpawn::create(
            CCSequence::create(
                CCDelayTime::create(0.2f),
                CCEaseSineOut::create(CCEaseBackOut::create(CCScaleTo::create(0.67f, 1.f))),
                CCDelayTime::create(0.9f),
                CCTintTo::create(0.f, 255, 255, 255),
                CCBlink::create(0.3f, 5),
                CCTintTo::create(0.f, 255, 0, 0),
                CCDelayTime::create(1.f),
                CCEaseSineOut::create(CCEaseBackIn::create(CCScaleTo::create(0.62f, 0.f))),
                nullptr
            ),
            CCSequence::create(
                CCDelayTime::create(0.2f),
                CCEaseIn::create(CCFadeTo::create(0.02f, 255), 2.f),
                CCDelayTime::create(0.2f),
                CCEaseInOut::create(CCTintTo::create(0.35f, 255, 0, 0), 2.f),
                nullptr
            ),
            nullptr
        )
    );

    m_shine3->runAction(
        CCSpawn::create(
            CCSequence::create(
                CCDelayTime::create(0.2f),
                CCEaseSineOut::create(CCEaseBackOut::create(CCScaleTo::create(0.67f, 1.f))),
                CCDelayTime::create(0.9f),
                CCTintTo::create(0.f, 120, 0, 0),
                CCBlink::create(0.3f, 5),
                CCTintTo::create(0.f, 255, 0, 0),
                CCDelayTime::create(1.f),
                CCEaseSineOut::create(CCEaseBackIn::create(CCScaleTo::create(0.62f, 0.f))),
                nullptr
            ),
            CCSequence::create(
                CCDelayTime::create(0.235f),
                CCEaseIn::create(CCFadeTo::create(0.02f, 177), 2.f),
                CCDelayTime::create(0.2f),
                CCEaseInOut::create(CCTintTo::create(0.35f, 140, 0, 0), 2.f),
                nullptr
            ),
            nullptr
        )
    );

    m_shine4->runAction(
        CCSpawn::create(
            CCSequence::create(
                CCDelayTime::create(0.2f),
                CCEaseSineOut::create(CCEaseBackOut::create(CCScaleTo::create(0.67f, 0.65f))),
                CCDelayTime::create(0.9f),
                CCTintTo::create(0.f, 120, 0, 0),
                CCBlink::create(0.3f, 5),
                CCTintTo::create(0.f, 255, 0, 0),
                CCDelayTime::create(1.f),
                CCEaseSineOut::create(CCEaseBackIn::create(CCScaleTo::create(0.62f, 0.f))),
                nullptr
            ),
            CCSequence::create(
                CCDelayTime::create(0.235f),
                CCEaseIn::create(CCFadeTo::create(0.02f, 255), 2.f),
                CCDelayTime::create(0.2f),
                CCEaseInOut::create(CCTintTo::create(0.35f, 255, 0, 0), 2.f),
                nullptr
            ),
            nullptr
        )
    );

    m_bg2->runAction(CCSequence::create(
        CCDelayTime::create(0.32f),
        CallFuncExt::create([this] {
            m_bg2->stopAllActions();
            m_bg2->setOpacity(255);
            m_bg2->setColor({0, 0, 0});
            m_bg2->runAction(CCSequence::create(
                CCBlink::create(0.28f, 6),
                CCHide::create(),
                nullptr
            ));
        }),
        nullptr
    ));

    m_layerColor->runAction(CCSequence::create(
        CCDelayTime::create(0.45f),
        CCHide::create(),
        CCDelayTime::create(0.02f),
        CCShow::create(),
        CCMoveBy::create(0.f, {4, 4}),
        CCDelayTime::create(0.02f),
        CCHide::create(),
        CCDelayTime::create(0.02f),
        CCMoveBy::create(0.f, {-8, -8}),
        CCShow::create(),
        CCDelayTime::create(0.05f),
        CCMoveBy::create(0.f, {8, 8}),
        CCDelayTime::create(0.15f),
        CCMoveBy::create(0.f, {-8, -8}),
        CCHide::create(),
        CCDelayTime::create(0.02f),
        CCMoveBy::create(0.f, {2, 2}),
        CCShow::create(),
        CCDelayTime::create(0.02f),
        CCHide::create(),
        CCDelayTime::create(0.02f),
        CCMoveBy::create(0.f, {-2, -2}),
        CCShow::create(),
        CallFuncExt::create([this] {
            m_bg2->stopAllActions();
            m_bg2->setColor({255, 255, 255});
            m_bg2->runAction(CCSequence::create(
                CCShow::create(),
                CCFadeTo::create(0.f, 45),
                CCDelayTime::create(0.1f),
                CCFadeTo::create(0.f, 0),
                nullptr
            ));

            m_redStar1->runAction(CCBlink::create(0.2f, 2));
            m_redStar2->runAction(CCBlink::create(0.3f, 3));
            m_shine1->runAction(CCBlink::create(0.4f, 4));
            m_shine2->runAction(CCBlink::create(0.4f, 4));
            m_shine3->runAction(CCBlink::create(0.4f, 4));
            m_shine4->runAction(CCBlink::create(0.4f, 4));
        }),
        CCDelayTime::create(0.2f),
        CCMoveTo::create(0.f, {0, -102}),
        nullptr
    ));
}

bool SecretPopup::init() {
    AchievementPopup::init();

    m_glow->setScaleY(4.4f);
    m_glow->setColor({ 123, 60, 60 });
    m_bg2->setColor({ 255, 163, 163 });

    auto crack = CCSprite::create("crack.png"_spr);
    crack->setScale(1.225f);
    crack->setOpacity(29);

    m_layerColor->addChild(crack, 1);

    m_redStar1 = CCSprite::create("red-star-1.png"_spr);
    m_redStar1->setPosition({161, -49});
    m_redStar1->setScale(0.f); // 0.85f
    m_redStar1->setRotation(25); // 0
    
    m_layerColor->addChild(m_redStar1);

    m_redStar2 = CCSprite::create("red-star-2.png"_spr);
    m_redStar2->setPosition({-173, 25});
    m_redStar2->setScale(0.f);
    m_redStar2->setRotation(-30); // -5
    
    m_layerColor->addChild(m_redStar2);

    m_shine1 = CCSprite::createWithSpriteFrameName("particle_169_001.png");
    m_shine1->setScale(0.f);
    m_shine1->setRotation(45);
    m_shine1->setPosition({-165, -5});
    m_shine1->setOpacity(0);

    m_layerColor->addChild(m_shine1);

    m_shine2 = CCSprite::createWithSpriteFrameName("particle_169_001.png");
    m_shine2->setScale(0.f);
    m_shine2->setRotation(45);
    m_shine2->setPosition({174, 3});
    m_shine2->setOpacity(0);

    m_layerColor->addChild(m_shine2);

    m_shine3 = CCSprite::createWithSpriteFrameName("particle_168_001.png");
    m_shine3->setScale(0.f);
    m_shine3->setRotation(45);
    m_shine3->setPosition({-164, -48});
    m_shine3->setOpacity(0);

    m_layerColor->addChild(m_shine3);

    m_shine4 = CCSprite::createWithSpriteFrameName("particle_167_001.png");
    m_shine4->setScale(0.f);
    m_shine4->setRotation(45);
    m_shine4->setPosition({-164, -48});
    m_shine4->setOpacity(0);

    m_layerColor->addChild(m_shine4);

    m_layer1 = CCLayerColor::create({100, 100, 100, 200}, 111, 24);
    m_layer1->setPosition({-163, -50});
    m_layer1->setVisible(false);

    m_layerColor->addChild(m_layer1, -1);
    
    m_layer2 = CCLayerColor::create({ 100, 100, 100, 200 }, 111, 24);
    m_layer2->setPosition({67, 26});
    m_layer2->setVisible(false);

    m_layerColor->addChild(m_layer2, -1);
    
    return true;
}