#include "../Includes.hpp"

class AchievementPopup;

class Utils {

public:

    static int getRandomInt(int, int);

    static AchievementPopup* createPopup(int);

    static float getPopupDuration(Rarity);

    static std::string getBadgeFilename(Rarity);

    static std::filesystem::path getSoundPath(Rarity);

    static float getSoundVolume(Rarity);
    
    static float getSoundPitch(Rarity);

    static float getBadgeScale(Rarity);

    static std::string getRarityName(Rarity);

    static std::vector<ccColor3B> getLabelColors(Rarity);

    static std::vector<ccColor3B> getTagLabelColors(Rarity);

    static ccColor3B interpolateColor(const ccColor3B&, const ccColor3B&, float);

    static void colorLabel(CCLabelBMFont*, const std::vector<ccColor3B>&);

    static void setHookEnabled(const std::string&, bool);

    static std::string getTimeString(int);

};