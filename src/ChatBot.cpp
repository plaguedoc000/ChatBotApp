#include "ChatBot.h"
#include "MainMenu.h"
#include "MenuItems.h"
#include <memory>

void ChatBot::run() {
    // Авторизация пользователя
    User* currentUser = authSystem.authenticate();
    
    // Создание главного меню
    MainMenu mainMenu(currentUser);
    
    // Добавление базовых пунктов меню
    mainMenu.addItem(new StartChatMenuItem());
    mainMenu.addItem(new HistoryMenuItem());
    mainMenu.addItem(new ProfileMenuItem());
    mainMenu.addItem(new HelpMenuItem());
    
    // Если пользователь - администратор, добавляем дополнительные пункты
    if (currentUser->isAdmin()) {
        mainMenu.addItem(new UserManagementMenuItem());
        mainMenu.addItem(new StatisticsMenuItem());
        mainMenu.addItem(new ChatbotSettingsMenuItem());
        mainMenu.addItem(new KnowledgeBaseMenuItem());
        mainMenu.addItem(new DemoMenuItem());
        mainMenu.addItem(new DemoMenuItem());
        mainMenu.addItem(new PolymorphismDemoMenuItem());
    }

    // Добавление пункта выхода
    mainMenu.addItem(new ExitMenuItem(mainMenu));
    
    // Отображение меню
    mainMenu.display();
}