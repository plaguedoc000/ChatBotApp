#ifndef CHATBOT_MAIN_MENU_H
#define CHATBOT_MAIN_MENU_H

#include <memory>
#include "Menu.h"
#include "User.h"

// Определение класса MainMenu (наследник класса Menu)
class MainMenu : public Menu {
private:
    User* currentUser;
    
public:
    MainMenu(User* user);
    ~MainMenu() override;
};

#endif // CHATBOT_MAIN_MENU_H