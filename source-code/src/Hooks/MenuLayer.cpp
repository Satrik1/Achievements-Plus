#include "MenuLayer.hpp"

#include "../Other/Manager.hpp"
#include "../Other/Utils.hpp"

#include "../UI/AchievementList.hpp"

void ProMenuLayer::onButtOn(CCObject*) {
    AchievementList::create()->show();
}

bool ProMenuLayer::init() {
    if (!MenuLayer::init()) {
        return false;
    }

    auto spr1 = CCSprite::create("button-icon.png"_spr);
    auto spr2 = CircleButtonSprite::create(spr1, CircleBaseColor::Green, CircleBaseSize::MediumAlt);
    spr1->setPositionX(26.6f);
    spr1->setScale(spr1->getScale() * 1.05f);

    auto menu = getChildByID("bottom-menu");
    auto btn = CCMenuItemSpriteExtra::create(
        spr2,
        this,
        menu_selector(ProMenuLayer::onButtOn)
    );

    menu->addChild(btn);
    menu->updateLayout();

    auto& am = Manager::get();

    if (!am.m_firstLoad) {
        return true;
    }

    am.m_firstLoad = false;
    am.checkAchievements();
    
    // Leave the game open without playing for 5 minutes
    if (!am.isAchievementCompleted(22)) {
        am.m_lastMovementTime = std::chrono::steady_clock::now();

        class Achievement22Updater : public CCObject {

        public:

            void update(float) {
                if (PlayLayer::get()) {
                    return;
                }
                
                constexpr auto window = std::chrono::minutes(5);
                auto& am = Manager::get();
                auto now = std::chrono::steady_clock::now();

                if (now - am.m_lastMovementTime > window) {
                    am.completeAchievement(22);
                    CCScheduler::get()->unscheduleAllForTarget(this);
                }
            }

        };

        auto updater = new Achievement22Updater();
        updater->retain();
        CCScheduler::get()->scheduleSelector(schedule_selector(Achievement22Updater::update), updater, 0.05f, kCCRepeatForever, 0.f, false);
    } else {
        Utils::setHookEnabled("cocos2d::CCTouchDispatcher::touches", false);
        Utils::setHookEnabled("cocos2d::CCKeyboardDispatcher::dispatchKeyboardMSG", false);
    }

    return true;
}
