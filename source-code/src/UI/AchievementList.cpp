#include "AchievementList.hpp"
#include "AchievementNode.hpp"

#include "../Other/Manager.hpp"

AchievementList::~AchievementList() {
    Manager::get().m_currentListPopup = nullptr;
}

AchievementList* AchievementList::create() {
    auto ret = new AchievementList();

    ret->initAnchored(300, 260);
    ret->autorelease();

    return ret;
}

ScrollLayer* AchievementList::getScrollLayer() {
    return m_scrollLayer;
}

void AchievementList::update() {
    auto ogY = m_scrollLayer->m_contentLayer->getPositionY();

    onClose(nullptr);

    auto list = AchievementList::create();
    list->m_noElasticity = true;
    list->show();
    list->getScrollLayer()->m_contentLayer->setPositionY(ogY);
}


bool AchievementList::setup() {
    setTitle("Achievements");

    Manager::get().m_currentListPopup = this;

    float gap = 5.f;

    m_scrollLayer = ScrollLayer::create({250, 200});
    m_scrollLayer->m_contentLayer->setLayout(
        ColumnLayout::create()
            ->setGap(gap)
            ->setAxisReverse(true)
            ->setAxisAlignment(AxisAlignment::End)
            ->setAutoGrowAxis(200.f)
    );

    auto filler = CCNode::create();
    filler->setContentHeight(gap / 4.f);
    m_scrollLayer->m_contentLayer->addChild(filler);

    for (int i = 1; i < 32; i++) {
        m_scrollLayer->m_contentLayer->addChild(AchievementNode::create(i));
    }

    filler = CCNode::create();
    filler->setContentHeight(gap / 4.f);
    m_scrollLayer->m_contentLayer->addChild(filler);

    m_scrollLayer->m_contentLayer->updateLayout();

    auto border = Border::create(m_scrollLayer, {138, 77, 46, 255}, {250, 200}, {0, 0});
    border->setPaddingBottom(0.3f);
    border->setPosition({25, 22});

    m_mainLayer->addChild(border);
    
    auto scrollbar = Scrollbar::create(m_scrollLayer);
    scrollbar->setPosition(border->getPosition() + ccp(255, 0));
    scrollbar->setAnchorPoint({0, 0});
    m_mainLayer->addChild(scrollbar, 5);
    
    m_scrollLayer->scrollToTop();

    return true;
}