#include "../Includes.hpp"

class AchievementList : public Popup<> {

private:

    ScrollLayer* m_scrollLayer = nullptr;

    bool setup() override;

    ~AchievementList();

public:

    static AchievementList* create();

    ScrollLayer* getScrollLayer();

    void update();

};