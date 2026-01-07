#include "../Includes.hpp"

class AchievementNode : public CCNode {

private:

    void init(int);

    void onInfo(CCObject*);
    void onCheckmark(CCObject*);

public:

    static AchievementNode* create(int);

};