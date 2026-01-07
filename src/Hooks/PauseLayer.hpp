#include "../Includes.hpp"

#include <Geode/modify/PauseLayer.hpp>

class $modify(ProPauseLayer, PauseLayer) {

    struct Fields {
        float m_time = 0.f;

        bool m_gameWasUnmuted = false;
    };

    void updateTime(float);

    void onResume(CCObject*);

    void customSetup();

    void checkMute();

    void musicSliderChanged(CCObject*);

    void sfxSliderChanged(CCObject*);

};