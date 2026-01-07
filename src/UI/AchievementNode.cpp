#include "AchievementNode.hpp"

#include "../Other/Manager.hpp"
#include "../Other/Utils.hpp"

#include "../UI/AchievementPopup.hpp"

void AchievementNode::onInfo(CCObject* sender) {
    auto id = static_cast<CCNode*>(sender)->getTag();

    auto& am = Manager::get();

    const auto& achievement = am.getAchievementById(id);

    auto title = std::string(achievement.title);
    auto description = std::string(achievement.description);

    geode::createQuickPopup(
        title.c_str(),
        fmt::format(
            "\"{}\"\n\n{}",
            description,
            am.isAchievementCompleted(id)
                ? fmt::format("Achievement Unlocked:\n<cl>{}</c>", Utils::getTimeString(id))
                : "<cl>Achievement Not Unlocked</c>"
        ),
        "Ok", nullptr, [](auto, bool btn2){}
    );
}

void AchievementNode::onCheckmark(CCObject* sender) {
    auto id = static_cast<CCNode*>(sender)->getTag();

    auto& am = Manager::get();

    if (am.m_currentPopup && am.m_currentPopup->getAchievementId() == id) {
        return;
    }

    for (auto popup : am.m_queuedPopups) {
        if (popup->getAchievementId() == id) {
            return;
        }
    }
    
    am.showAchievement(id);
}

AchievementNode* AchievementNode::create(int id) {
    auto ret = new AchievementNode();

    ret->init(id);
    ret->autorelease();

    return ret;
}

void AchievementNode::init(int id) {
    setContentSize({250, 48});
    setAnchorPoint({0, 0});

    auto& am = Manager::get();

    const auto& achievement = am.getAchievementById(id);

    auto title = std::string(achievement.title);

    auto menu = CCMenu::create();
    menu->setPosition({0, 0});

    addChild(menu, 6);

    auto bg = CCScale9Sprite::create("square02b_001.png");
    bg->setOpacity(30);
    bg->setColor({0, 0, 0});    
    bg->setScale(0.9f);
    bg->setContentSize(ccp(238, getContentHeight()) / bg->getScale());
    bg->setPosition({6, 0});
    bg->setAnchorPoint({0, 0});

    addChild(bg, -5);

    auto badge = CCSprite::create(Utils::getBadgeFilename(achievement.rarity).c_str());
    badge->setScale(33.92f / badge->getContentSize().width * Utils::getBadgeScale(achievement.rarity));
    badge->setPosition({29, 24});
    
    addChild(badge, 1);

    auto badgeShadow = CCSprite::create(Utils::getBadgeFilename(achievement.rarity).c_str());
    badgeShadow->setOpacity(78);
    badgeShadow->setColor({0, 0, 0});
    badgeShadow->setScale(badge->getScale());
    badgeShadow->setPosition(badge->getPosition() + ccp(1.2f, -2));

    addChild(badgeShadow);

    auto titleLabel = CCLabelBMFont::create(title.c_str(), "bigFont.fnt");
    titleLabel->setAnchorPoint({0.f, 0.5f});
    titleLabel->setPosition({53.5f, 35.f});
    titleLabel->limitLabelWidth(167.f, 0.425f, 0.0001f);

    addChild(titleLabel);

    Utils::colorLabel(titleLabel, Utils::getLabelColors(achievement.rarity));
    
    auto spr = CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png");
    spr->setScale(0.465f);

    auto btn = CCMenuItemSpriteExtra::create(spr, this, menu_selector(AchievementNode::onInfo));
    btn->setTag(id);
    btn->setPosition({235.5f, 40});
    
    menu->addChild(btn);

    auto tagBg = CCScale9Sprite::create("square02b_001.png");
    tagBg->setOpacity(30);
    tagBg->setColor({0, 0, 0});    
    tagBg->setScale(0.22f);
    tagBg->setContentSize(ccp(55, 13) / tagBg->getScale());
    tagBg->setPosition({53.5f, 8});
    tagBg->setAnchorPoint({0, 0});

    addChild(tagBg, -5);

    auto tagLabel = CCLabelBMFont::create(Utils::getRarityName(achievement.rarity).c_str(), "bigFont.fnt");
    tagLabel->setScale(0.325f);
    tagLabel->setPosition(tagBg->getPosition() + tagBg->getScaledContentSize() / 2.f + ccp(0, 1));

    addChild(tagLabel);

    Utils::colorLabel(tagLabel, Utils::getTagLabelColors(achievement.rarity));

    if (!am.isAchievementCompleted(id)) {
        auto overlay = CCScale9Sprite::create("square02b_001.png");
        overlay->setOpacity(20);
        overlay->setColor({0, 0, 0});    
        overlay->setScale(0.9f);
        overlay->setContentSize(ccp(238, getContentHeight()) / overlay->getScale());
        overlay->setPosition({6, 0});
        overlay->setAnchorPoint({0, 0});

        addChild(overlay, 5);

        auto lock = CCSprite::createWithSpriteFrameName("GJLargeLock_001.png");
        lock->setScale(0.18f);
        lock->setPosition({235.5f, 10});
        
        addChild(lock, 5);

        badge->setOpacity(90);
        titleLabel->setOpacity(130);
        tagBg->setOpacity(15);
        tagLabel->setOpacity(90);
    } else {
        auto checkmark = CCSprite::createWithSpriteFrameName("GJ_completesIcon_001.png");
        checkmark->setScale(0.48f);

        auto checkmarkBtn = CCMenuItemSpriteExtra::create(checkmark, this, menu_selector(AchievementNode::onCheckmark));
        checkmarkBtn->setTag(id);
        checkmarkBtn->setPosition({235.5f, 9});
        
        menu->addChild(checkmarkBtn, 5);
    }

    switch (achievement.rarity) {
        default:
        case Rarity::Normal: {
            auto particle = GameToolbox::particleFromStruct(
                {
                    2,-1,2,1,2,90,0,4,2,50,2,0,0,0,0,0,0,9,5,0,0,0.0823529,0,1,0,0.152941,0,1,0.46,9,0,0,0,0.690196,0,1,0,0.682353,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,false,false,false,false,27,false,0,0,0,0,false,false,false,false,false,0,0,0,0,"particle_27_001.png"
                },
                nullptr,
                false
            );
            particle->setScale(0.41f);
            particle->setPosition({tagLabel->getPositionX(), 19});

            addChild(particle, -2);
            break;
        }
        case Rarity::Special: {
            auto particle = GameToolbox::particleFromStruct(
                {
                    2,-1,2,1.25,2,90,0,4,2,50,7,0,0,0,0,0,0,9,5,0,0,1,0,0.0784314,0,0.823529,0,1,0.46,9,0,0,0,0,0,0.913725,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,false,false,false,false,27,false,0,0,0,0,false,false,false,false,false,0,0,0,0,"particle_27_001.png"
                },
                nullptr,
                false
            );
            particle->setScale(0.41f);
            particle->setPosition({tagLabel->getPositionX(), 19});

            addChild(particle, -2);

            auto rainbow = CCSprite::create("rainbow-1.png"_spr);
            rainbow->setScale(0.18f);
            rainbow->setRotation(-90);
            rainbow->setPosition({54, 14.5f});
            rainbow->setOpacity(100);

            addChild(rainbow);

            rainbow->runAction(CCRepeatForever::create(
                CCSequence::create(
                    CCFadeTo::create(0.1f, 70),
                    CCFadeTo::create(0.1f, 82),
                    CCFadeTo::create(0.1f, 70),
                    CCFadeTo::create(0.1f, 82),
                    CCDelayTime::create(0.2f),
                    nullptr
                )
            ));

            rainbow = CCSprite::create("rainbow-1.png"_spr);
            rainbow->setScale(0.18f);
            rainbow->setRotation(90);
            rainbow->setPosition({54 + tagBg->getScaledContentWidth(), 14.5f});
            rainbow->setOpacity(100);

            addChild(rainbow);

            rainbow->runAction(CCRepeatForever::create(
                CCSequence::create(
                    CCFadeTo::create(0.1f, 70),
                    CCFadeTo::create(0.1f, 82),
                    CCFadeTo::create(0.1f, 70),
                    CCFadeTo::create(0.1f, 82),
                    CCDelayTime::create(Utils::getRandomInt(1, 10) / 10.f),
                    nullptr
                )
            ));

            break;
        }
        case Rarity::Secret: {
            if (am.isAchievementCompleted(id)) {
                tagBg->setOpacity(55);
                tagLabel->setOpacity(199);
            }

            auto particle = GameToolbox::particleFromStruct(
                {
                    2,-1,2,1.25,2,90,0,4,2,50,7,0,0,0,0,0,0,9,5,0,0,0,0,0,0,0,0,1,0.26,9,0,0,0,0.5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,false,false,false,false,27,false,0,0,0,0,false,false,false,false,false,0,0,0,0,"particle_27_001.png"
                },
                nullptr,
                false
            );
            particle->setScaleX(0.41f);
            particle->setScaleY(-0.41f);
            particle->setPosition({tagLabel->getPositionX(), 12});

            addChild(particle, -2);

            auto ogPos = tagLabel->getPosition();

            tagLabel->runAction(CCRepeatForever::create(
                CCSequence::create(
                    CCDelayTime::create(0.5f),
                    CallFuncExt::create([tagLabel, ogPos] {
                        tagLabel->runAction(CCSequence::create(
                            CCDelayTime::create(Utils::getRandomInt(1, 10) / 10.f),
                            CallFuncExt::create([tagLabel = Ref(tagLabel)] {
                                auto children = tagLabel->getChildrenExt<CCFontSprite*>();
                                auto random = Utils::getRandomInt(0, children.size() - 1);

                                children[random]->runAction(CCSequence::create(
                                    CCHide::create(),
                                    CCDelayTime::create(0.05f),
                                    CCShow::create(),
                                    nullptr
                                ));
                            }),
                            nullptr
                        ));

                        tagLabel->runAction(CCSequence::create(
                            CCDelayTime::create(Utils::getRandomInt(5, 7) / 10.f),
                            CallFuncExt::create([tagLabel, ogPos] {
                                tagLabel->setPosition(ogPos + ccp(
                                    Utils::getRandomInt(-1, 1),
                                    Utils::getRandomInt(-1, 1)
                                ));
                            }),
                            CCDelayTime::create(0.02f),
                            CallFuncExt::create([tagLabel, ogPos] {
                                tagLabel->setPosition(ogPos);
                            }),
                            nullptr
                        ));
                    }),
                    nullptr
                )
            ));

            auto time = Utils::getRandomInt(90, 230) / 100.f;

            auto layer = CCLayerColor::create({140, 140, 140, 0}, 17, 6);
            layer->setPosition({58, 9});
            layer->runAction(CCRepeatForever::create(
                CCSequence::create(
                    CCDelayTime::create(time),
                    CCFadeTo::create(0.f, 20),
                    CCDelayTime::create(0.07f),
                    CCFadeTo::create(0.f, 0),
                    nullptr
                )
            ));

            addChild(layer, -1);

            layer = CCLayerColor::create({100, 100, 100, 0}, 17, 6);
            layer->setPosition({85, 14});
            layer->runAction(CCRepeatForever::create(
                CCSequence::create(
                    CCDelayTime::create(time + 0.15f),
                    CCFadeTo::create(0.f, 20),
                    CCDelayTime::create(0.07f),
                    CCFadeTo::create(0.f, 0),
                    nullptr
                )
            ));

            addChild(layer, -1);

            layer = CCLayerColor::create({0, 0, 0, 0}, 15, 6);
            layer->setPosition({63, 15});
            layer->runAction(CCRepeatForever::create(
                CCSequence::create(
                    CCDelayTime::create(time + 0.05f),
                    CCFadeTo::create(0.f, 15),
                    CCDelayTime::create(0.07f),
                    CCFadeTo::create(0.f, 0),
                    nullptr
                )
            ));

            addChild(layer, -1);

            break;
        }
        case Rarity::Divine: {
            auto glow = CCSprite::create("glow.png"_spr);
            glow->setScaleX(0.625f);
            glow->setScaleY(0.19f);
            glow->setPosition({80.6f, 9.3f});
            glow->runAction(CCRepeatForever::create(
                CCSequence::create(
                    CCFadeTo::create(0.05f, 200),
                    CCFadeTo::create(0.05f, 255),
                    nullptr
                )
            ));

            addChild(glow);

            auto particle = GameToolbox::particleFromStruct(
                {
                    30,-1,1.64,0.3,15,90,0,5,3,65,11,0,-1,0,0,0,0,8,1,0,0,1,0,0.988235,0,0.87,0,0.77,0,8,0,0,0,1,0,0.984314,0,0.666667,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,true,false,false,false,173,false,0,0,0,0,false,false,false,false,false,0,0,0,0,"particle_173_001.png"
                },
                nullptr,
                false
            );
            particle->setScale(0.41f);
            particle->setPosition({tagLabel->getPositionX(), 13.5f});

            addChild(particle, -2);

            auto wing1 = CCSprite::create("wing.png"_spr);
            wing1->setPosition({109, 15.3f});
            wing1->setScale(0.467f);

            addChild(wing1);

            auto wing2 = CCSprite::create("wing.png"_spr);
            wing2->setPosition({54, 15.3f});
            wing2->setScale(0.467f);
            wing2->setFlipX(true);

            addChild(wing2);

            if (!am.isAchievementCompleted(id)) {
                glow->setOpacity(90);
                wing1->setOpacity(90);
                wing2->setOpacity(90);
            }

            break;
        }
    }
}