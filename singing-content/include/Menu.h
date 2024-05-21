#ifndef MENU_H
#define MENU_H

#include "ContestManager.h"

class Menu {
   private:
    ContestManager manager;
    void displayMainMenu();
    void displayManageMenu();
    void displaySortMenu();
    void displayFileMenu();

   public:
    void start();
};

#endif  // MENU_H
