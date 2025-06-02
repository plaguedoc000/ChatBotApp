#ifndef CHATBOT_MAIN_MENU_H
#define CHATBOT_MAIN_MENU_H

#include "Menu.h"
#include "User.h"

class MainMenu : public Menu {
private:
    User* currentUser;

public:
    MainMenu(User* user);
    ~MainMenu() override = default;
};

#endif // CHATBOT_MAIN_MENU_H
