#include "MainMenu.h"

MainMenu::MainMenu(User* user)
    : Menu("Главное меню — " + (user ? user->getRole() : "")),
      currentUser(user)
{}
