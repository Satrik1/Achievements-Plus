#include "AppDelegate.hpp"
#include "CCTouchDispatcher.hpp"

#include "../Other/Manager.hpp"

void ProAppDelegate::trySaveGame(bool p0) {
    Manager::get().save();

    AppDelegate::trySaveGame(p0);
}
