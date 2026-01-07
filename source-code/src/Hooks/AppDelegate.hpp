#include "../Includes.hpp"

#include <Geode/modify/AppDelegate.hpp>

class $modify(ProAppDelegate, AppDelegate) {

    static void onModify(auto& self) {
        (void)self.setHookPriorityBeforePre("AppDelegate::trySaveGame", "geode.loader");
    }

    void trySaveGame(bool p0);

};