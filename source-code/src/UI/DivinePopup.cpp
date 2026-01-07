#include "DivinePopup.hpp"

void DivinePopup::spawnParticle(const CCPoint& pos) {
    auto particle = GameToolbox::particleFromStruct(
        {
            46,-1,0.55,0,-1,-180,180,147,42,7,5,0,-640,0,0,0,0,22,1,0,0,0.988235,0,1,0,0.576471,0,1,0,1,1,0,0,1,0,0.964706,0,0.694118,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,true,false,false,false,173,false,0,0,0,0,false,false,false,false,false,0,0,0,0,"particle_173_001.png"
        },
        nullptr,
        false
    );
    particle->setScale(0.7f);
    particle->setPosition(pos);
    particle->setAutoRemoveOnFinish(true);

    m_layerColor->addChild(particle, 4);

    m_gradient2->stopAllActions();
    m_gradient2->runAction(CCSequence::create(
        CCFadeTo::create(0.02f, 30),
        CCFadeTo::create(0.35f, 0),
        nullptr
    ));
}

void DivinePopup::show() {
    AchievementPopup::show();

    this->runAction(CCSequence::create(
        CCDelayTime::create(0.42f),
        CallFuncExt::create([this] {
            spawnParticle({-214, -46});
        }),
        CCDelayTime::create(0.31f),
        CallFuncExt::create([this] {
            spawnParticle({-24, -78});
        }),
        CCDelayTime::create(0.355f),
        CallFuncExt::create([this] {
            spawnParticle({57, -70});
        }),
        CCDelayTime::create(0.205f),
        CallFuncExt::create([this] {
            spawnParticle({236, -14});
            m_gradient2->stopAllActions();
            m_gradient2->runAction(CCSequence::create(
                CCFadeTo::create(0.05f, 95),
                CCFadeTo::create(2.f, 0),
                nullptr
            ));
        }),
        nullptr
    ));

    auto ogScale = m_whiteBadge->getScale();
    auto ogOpacity = m_badgeShadow->getOpacity();

    m_badge->setScale(ogScale * 1.1f);
    m_badgeShadow->setOpacity(0);
    m_badgeShadow->setScale(ogScale * 1.1f);
    m_whiteBadge->setScale(ogScale * 1.1f);

    m_badge->runAction(CCEaseSineInOut::create(CCScaleTo::create(1.5f, ogScale)));
    
    m_badgeShadow->runAction(CCSpawn::create(
        CCEaseSineInOut::create(CCScaleTo::create(1.5f, ogScale)),
        CCEaseSineInOut::create(CCFadeTo::create(2.1f, ogOpacity)),
        nullptr
    ));

    m_whiteBadge->runAction(CCSpawn::create(
        CCEaseSineInOut::create(CCFadeOut::create(1.5f)),
        CCEaseSineInOut::create(CCScaleTo::create(1.5f, ogScale)),
        nullptr
    ));

    m_bg2->stopAllActions();
    m_bg2->runAction(CCEaseInOut::create(CCFadeOut::create(0.59f), 1.8f));

    m_overlay->setPosition(-getPosition());
    m_overlay->runAction(CCSequence::create(
        CCEaseSineIn::create(CCFadeTo::create(0.15f, 60)),
        CCFadeTo::create(3.8f, 0),
        nullptr
    ));

    m_gradient1->runAction(CCSequence::create(
        CCEaseSineIn::create(CCFadeTo::create(0.06f, 130)),
        CCFadeTo::create(3.8f, 0),
        nullptr
    ));

    m_glow->stopAllActions();
    m_glow->runAction(CCEaseInOut::create(CCFadeTo::create(0.35f, 255), 2.f));

    m_shine1->runAction(
        CCSpawn::create(
            CCSequence::create(
                CCDelayTime::create(0.2f),
                CCEaseSineOut::create(CCEaseBackOut::create(CCScaleTo::create(0.67f, 0.65f))),
                CCDelayTime::create(3.2f),
                CCEaseSineOut::create(CCEaseBackIn::create(CCScaleTo::create(0.62f, 0.f))),
                nullptr
            ),
            CCSequence::create(
                CCDelayTime::create(0.2f),
                CCEaseIn::create(CCFadeTo::create(0.02f, 255), 2.f),
                CCDelayTime::create(0.2f),
                CCEaseInOut::create(CCTintTo::create(0.35f, 255, 253, 139), 2.f),
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
                CCDelayTime::create(3.2f),
                CCEaseSineOut::create(CCEaseBackIn::create(CCScaleTo::create(0.62f, 0.f))),
                nullptr
            ),
            CCSequence::create(
                CCDelayTime::create(0.2f),
                CCEaseIn::create(CCFadeTo::create(0.02f, 255), 2.f),
                CCDelayTime::create(0.2f),
                CCEaseInOut::create(CCTintTo::create(0.35f, 255, 253, 139), 2.f),
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
                CCDelayTime::create(3.2f),
                CCEaseSineOut::create(CCEaseBackIn::create(CCScaleTo::create(0.62f, 0.f))),
                nullptr
            ),
            CCSequence::create(
                CCDelayTime::create(0.235f),
                CCEaseIn::create(CCFadeTo::create(0.02f, 149), 2.f),
                CCDelayTime::create(0.2f),
                CCEaseInOut::create(CCTintTo::create(0.35f, 172, 169, 92), 2.f),
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
                CCDelayTime::create(3.2f),
                CCEaseSineOut::create(CCEaseBackIn::create(CCScaleTo::create(0.62f, 0.f))),
                nullptr
            ),
            CCSequence::create(
                CCDelayTime::create(0.235f),
                CCEaseIn::create(CCFadeTo::create(0.02f, 255), 2.f),
                CCDelayTime::create(0.2f),
                CCEaseInOut::create(CCTintTo::create(0.35f, 255, 251, 178), 2.f),
                nullptr
            ),
            nullptr
        )
    );

    m_shine5->runAction(
        CCSpawn::create(
            CCSequence::create(
                CCDelayTime::create(0.2f),
                CCEaseSineOut::create(CCEaseBackOut::create(CCScaleTo::create(0.67f, 1.f))),
                CCDelayTime::create(3.2f),
                CCEaseSineOut::create(CCEaseBackIn::create(CCScaleTo::create(0.62f, 0.f))),
                nullptr
            ),
            CCSequence::create(
                CCDelayTime::create(0.235f),
                CCEaseIn::create(CCFadeTo::create(0.02f, 149), 2.f),
                CCDelayTime::create(0.2f),
                CCEaseInOut::create(CCTintTo::create(0.35f, 172, 169, 92), 2.f),
                nullptr
            ),
            nullptr
        )
    );

    m_shine6->runAction(
        CCSpawn::create(
            CCSequence::create(
                CCDelayTime::create(0.2f),
                CCEaseSineOut::create(CCEaseBackOut::create(CCScaleTo::create(0.67f, 0.65f))),
                CCDelayTime::create(3.2f),
                CCEaseSineOut::create(CCEaseBackIn::create(CCScaleTo::create(0.62f, 0.f))),
                nullptr
            ),
            CCSequence::create(
                CCDelayTime::create(0.235f),
                CCEaseIn::create(CCFadeTo::create(0.02f, 255), 2.f),
                CCDelayTime::create(0.2f),
                CCEaseInOut::create(CCTintTo::create(0.35f, 255, 251, 178), 2.f),
                nullptr
            ),
            nullptr
        )
    );

    m_shine1->runAction(CCRepeatForever::create(
        CCSequence::create(
            CCFadeTo::create(0.05f, 225),
            CCFadeTo::create(0.05f, 255),
            nullptr
        )
    ));

    m_shine2->runAction(CCRepeatForever::create(
        CCSequence::create(
            CCFadeTo::create(0.05f, 225),
            CCFadeTo::create(0.05f, 255),
            nullptr
        )
    ));

    m_shine4->runAction(CCRepeatForever::create(
        CCSequence::create(
            CCFadeTo::create(0.05f, 225),
            CCFadeTo::create(0.05f, 255),
            nullptr
        )
    ));

    m_shine6->runAction(CCRepeatForever::create(
        CCSequence::create(
            CCFadeTo::create(0.05f, 225),
            CCFadeTo::create(0.05f, 255),
            nullptr
        )
    ));

    m_shine7->runAction(CCRepeatForever::create(
        CCSequence::create(
            CCFadeTo::create(0.05f, 225),
            CCFadeTo::create(0.05f, 255),
            nullptr
        )
    ));

    m_shine7->runAction(
        CCSpawn::create(
            CCSequence::create(
                CCDelayTime::create(0.2f),
                CCEaseSineOut::create(CCEaseBackOut::create(CCScaleTo::create(0.67f, 0.65f))),
                CCDelayTime::create(3.2f),
                CCEaseSineOut::create(CCEaseBackIn::create(CCScaleTo::create(0.62f, 0.f))),
                nullptr
            ),
            CCSequence::create(
                CCDelayTime::create(0.2f),
                CCEaseIn::create(CCFadeTo::create(0.02f, 255), 2.f),
                CCDelayTime::create(0.2f),
                CCEaseInOut::create(CCTintTo::create(0.35f, 255, 253, 139), 2.f),
                nullptr
            ),
            nullptr
        )
    );

    m_particle1->runAction(CCSequence::create(
        CCDelayTime::create(4.5f),
        CCEaseSineIn::create(CCMoveBy::create(0.35f, {0, 40})),
        nullptr
    ));

    m_particle2->runAction(CCSequence::create(
        CCDelayTime::create(4.f),
        CCEaseSineIn::create(CCMoveBy::create(1.f, {0, 100})),
        nullptr
    ));

    m_particle3->runAction(CCSequence::create(
        CCDelayTime::create(4.5f),
        CCEaseSineIn::create(CCMoveBy::create(0.35f, {0, 40})),
        nullptr
    ));

    m_particle4->runAction(CCSequence::create(
        CCDelayTime::create(4.5f),
        CCEaseSineIn::create(CCMoveBy::create(0.35f, {0, 40})),
        nullptr
    ));

    m_particle5->runAction(CCSequence::create(
        CCDelayTime::create(4.5f),
        CCEaseSineIn::create(CCMoveBy::create(0.35f, {0, 40})),
        nullptr
    ));
}

bool DivinePopup::init() {
    AchievementPopup::init();

    m_bg->removeFromParent();

    m_bg = CCScale9Sprite::create("gold-square.png"_spr);
    m_bg->setContentSize({300, 80});

    m_layerColor->addChild(m_bg);

    m_glow->setScaleY(4.3f);
    m_glow->setZOrder(-2);
    m_glow->setColor({ 253, 255, 117 });
    m_bg2->setColor({ 253, 255, 194 });

    auto winSize = CCDirector::get()->getWinSize();

    m_gradient1 = CCSprite::createWithSpriteFrameName("d_gradient_01_001.png");
    m_gradient1->setAnchorPoint({0.5f, 1.f});
    m_gradient1->setFlipY(true);
    m_gradient1->setPositionY(-50);
    m_gradient1->setColor({255, 241, 210});
    m_gradient1->setScaleX(winSize.width / m_gradient1->getContentWidth());
    m_gradient1->setScaleY(3.2f);
    m_gradient1->setOpacity(0);

    addChild(m_gradient1);

    m_gradient2 = CCSprite::createWithSpriteFrameName("d_gradient_01_001.png");
    m_gradient2->setAnchorPoint({0.5f, 1.f});
    m_gradient2->setFlipY(true);
    m_gradient2->setPositionY(-50);
    m_gradient2->setColor({255, 241, 210});
    m_gradient2->setScaleX(winSize.width / m_gradient2->getContentWidth());
    m_gradient2->setScaleY(3.2f);
    m_gradient2->setOpacity(0);

    addChild(m_gradient2);

    m_overlay = CCLayerColor::create({0, 0, 0, 0}, winSize.width, winSize.height);
    m_overlay->setAnchorPoint({0, 0});

    addChild(m_overlay, -1);

    m_whiteBadge = CCSprite::create("white-divine-badge.png"_spr);
    m_whiteBadge->setPosition(m_badge->getPosition());
    m_whiteBadge->setScale(m_badge->getScale());
    
    m_layerColor->addChild(m_whiteBadge, 3);

    m_particle1 = GameToolbox::particleFromStruct(
        {
            200,-1,1,0.3,153,88,180,39,0,200,58,0,0,0,0,0,0,1,1,0,0,1,0,0.988235,0,0.866667,0,1,0,1,0,0,0,1,0,0.984314,0,0.666667,0,1,0,0,0,0,0,0,0,0,0,0,0,0,2,true,false,false,false,0,false,0,0,0,0,false,false,false,false,false,0,0,0,0,"particle_00_001.png"
        },
        nullptr,
        false
    );
    m_particle1->setScale(0.75f);

    m_layerColor->addChild(m_particle1, -1);

    auto particle = GameToolbox::particleFromStruct(
        {
            9,-1,1,0.3,6,88,180,0,0,21,17,0,0,0,0,0,0,1,1,0,0,1,0,0.988235,0,0.866667,0,1,0,1,0,0,0,1,0,0.984314,0,0.666667,0,1,0,0,0,0,0,0,0,0,0,0,0,0,2,true,false,false,false,0,false,0,0,0,0,false,false,false,false,false,0,0,0,0,"particle_00_001.png"    
        },
        nullptr,
        false
    );
    particle->setScale(0.325f);
    particle->setPosition({-165, -5});

    m_layerColor->addChild(particle, -1);
    
    particle = GameToolbox::particleFromStruct(
        {
            9,-1,1,0.3,6,88,180,0,0,21,17,0,0,0,0,0,0,1,1,0,0,1,0,0.988235,0,0.866667,0,1,0,1,0,0,0,1,0,0.984314,0,0.666667,0,1,0,0,0,0,0,0,0,0,0,0,0,0,2,true,false,false,false,0,false,0,0,0,0,false,false,false,false,false,0,0,0,0,"particle_00_001.png"    
        },
        nullptr,
        false
    );
    particle->setScale(0.325f);
    particle->setPosition({174, 3});

    m_layerColor->addChild(particle, -1);

    m_particle4 = GameToolbox::particleFromStruct(
        {
            9,-1,1,0.3,6,88,180,0,0,21,17,0,0,0,0,0,0,1,1,0,0,1,0,0.988235,0,0.866667,0,1,0,1,0,0,0,1,0,0.984314,0,0.666667,0,1,0,0,0,0,0,0,0,0,0,0,0,0,2,true,false,false,false,0,false,0,0,0,0,false,false,false,false,false,0,0,0,0,"particle_00_001.png"    
        },
        nullptr,
        false
    );
    m_particle4->setScale(0.325f);
    m_particle4->setPosition({-164, -48});

    m_layerColor->addChild(m_particle4, -1);

    m_particle5 = GameToolbox::particleFromStruct(
        {
            9,-1,1,0.3,6,88,180,0,0,21,17,0,0,0,0,0,0,1,1,0,0,1,0,0.988235,0,0.866667,0,1,0,1,0,0,0,1,0,0.984314,0,0.666667,0,1,0,0,0,0,0,0,0,0,0,0,0,0,2,true,false,false,false,0,false,0,0,0,0,false,false,false,false,false,0,0,0,0,"particle_00_001.png"    
        },
        nullptr,
        false
    );
    m_particle5->setScale(0.325f);
    m_particle5->setPosition({174, -48});

    m_layerColor->addChild(m_particle5, -1);

    m_particle3 = GameToolbox::particleFromStruct(
        {
            9,-1,1,0.3,6,88,180,0,0,21,17,0,0,0,0,0,0,1,1,0,0,1,0,0.988235,0,0.866667,0,1,0,1,0,0,0,1,0,0.984314,0,0.666667,0,1,0,0,0,0,0,0,0,0,0,0,0,0,2,true,false,false,false,0,false,0,0,0,0,false,false,false,false,false,0,0,0,0,"particle_00_001.png"    
        },
        nullptr,
        false
    );
    m_particle3->setScale(0.325f);
    m_particle3->setPosition({144, -56});

    m_layerColor->addChild(m_particle3, -1);

    m_particle2 = GameToolbox::particleFromStruct(
        {
            200,-1,1.77,0,25,-90,0,64,43,280,0,0,22,0,0,0,0,40,1,0,0,1,0,0.976471,0,0.819608,0,0.57,0,0,0,0,0,1,0,0.984314,0,0.67,0,0.14,0,0,0,0,0,0,0,0,0,0,0,0,2,true,false,false,false,158,false,0,0,0,0,false,false,false,false,false,0,0,0,0,"particle_158_001.png"
        },
        nullptr,
        false
    );

    addChild(m_particle2, -1);

    auto ring = CCSprite::create("ring.png"_spr);
    ring->setSkewX(45);
    ring->setPosition({-147, 37});
    ring->setScale(0.55f);

    m_layerColor->addChild(ring, -1);

    ring = CCSprite::create("ring.png"_spr);
    ring->setSkewX(45);
    ring->setPosition({-147, 37});
    ring->setScale(0.4f);

    m_layerColor->addChild(ring, -1);

    ring = CCSprite::create("ring.png"_spr);
    ring->setSkewX(45);
    ring->setPosition({-147, 37});
    ring->setScale(0.25f);

    m_layerColor->addChild(ring, -1);

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

    m_shine5 = CCSprite::createWithSpriteFrameName("particle_168_001.png");
    m_shine5->setScale(0.f);
    m_shine5->setRotation(45);
    m_shine5->setPosition({174, -48});
    m_shine5->setOpacity(0);

    m_layerColor->addChild(m_shine5);

    m_shine6 = CCSprite::createWithSpriteFrameName("particle_167_001.png");
    m_shine6->setScale(0.f);
    m_shine6->setRotation(45);
    m_shine6->setPosition({174, -48});
    m_shine6->setOpacity(0);

    m_layerColor->addChild(m_shine6);

    m_shine7 = CCSprite::createWithSpriteFrameName("particle_169_001.png");
    m_shine7->setScale(0.f);
    m_shine7->setRotation(45);
    m_shine7->setPosition({144, -56});
    m_shine7->setOpacity(0);

    m_layerColor->addChild(m_shine7);
    
    return true;
}