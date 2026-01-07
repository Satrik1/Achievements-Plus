#include "CCScene.hpp"

#include "../Other/Manager.hpp"
#include "../UI/AchievementPopup.hpp"

int ProCCScene::getHighestChildZ() {
    auto& am = Manager::get();

    if (am.m_currentPopup) {
        auto prev = am.m_currentPopup->getZOrder();

        am.m_currentPopup->setZOrder(0);

        auto ret = CCScene::getHighestChildZ();

        am.m_currentPopup->setZOrder(prev);

        return ret;
    }

    return CCScene::getHighestChildZ();
}