#ifndef CHATBOT_MENU_ITEMS_H
#define CHATBOT_MENU_ITEMS_H

#include "MenuItem.h"
#include "Menu.h"

#include <iostream>
#include <limits>

// Определение класса ExitMenuItem (пункт меню для выхода)
class ExitMenuItem : public MenuItem {
private:
    Menu& parentMenu;
    
public:
    ExitMenuItem(Menu& menu);
    void execute() override;
};

// Определение конкретных пунктов меню
class StartChatMenuItem : public MenuItem {
public:
    StartChatMenuItem();
};

class HistoryMenuItem : public MenuItem {
public:
    HistoryMenuItem();
};

class ProfileMenuItem : public MenuItem {
public:
    ProfileMenuItem();
};

class HelpMenuItem : public MenuItem {
public:
    HelpMenuItem();
};

// Пункты меню администратора
class UserManagementMenuItem : public MenuItem {
public:
    UserManagementMenuItem();
};

class StatisticsMenuItem : public MenuItem {
public:
    StatisticsMenuItem();
};

class ChatbotSettingsMenuItem : public MenuItem {
public:
    ChatbotSettingsMenuItem();
};

class KnowledgeBaseMenuItem : public MenuItem {
public:
    KnowledgeBaseMenuItem();
};

class DemoMenuItem : public MenuItem {
    public:
        DemoMenuItem();
        void execute() override;
    };

class PolymorphismDemoMenuItem : public MenuItem {
        public:
            PolymorphismDemoMenuItem();
            void execute() override;
        };



#endif // CHATBOT_MENU_ITEMS_H