#include "MenuItems.h"
#include "User.h"
#include <iostream>
#include <limits>

ExitMenuItem::ExitMenuItem(Menu& menu) 
    : MenuItem("Выход", 0), parentMenu(menu) {}

void ExitMenuItem::execute() {
    std::cout << "Выход из программы..." << std::endl;
    parentMenu.requestExit();
}

StartChatMenuItem::StartChatMenuItem() 
    : MenuItem("Начать новый диалог", 1) {}

HistoryMenuItem::HistoryMenuItem() 
    : MenuItem("Просмотреть историю диалогов", 2) {}

ProfileMenuItem::ProfileMenuItem() 
    : MenuItem("Изменить настройки профиля", 3) {}

HelpMenuItem::HelpMenuItem() 
    : MenuItem("Помощь", 4) {}

UserManagementMenuItem::UserManagementMenuItem() 
    : MenuItem("Управление пользователями", 5) {}

StatisticsMenuItem::StatisticsMenuItem() 
    : MenuItem("Просмотр статистики использования", 6) {}

ChatbotSettingsMenuItem::ChatbotSettingsMenuItem() 
    : MenuItem("Настройки чатбота", 7) {}

KnowledgeBaseMenuItem::KnowledgeBaseMenuItem() 
    : MenuItem("Обновление базы знаний", 8) {}

DemoMenuItem::DemoMenuItem() : MenuItem("Демонстрация классов и объектов", 9) { }

void DemoMenuItem::execute() {
    std::cout << "=== Демонстрация возможностей классов ===\n" << std::endl;
    std::cout << "Выберите тип объекта для создания:" << std::endl;
    std::cout << "1. Создать RegularUser" << std::endl;
    std::cout << "2. Создать Administrator" << std::endl;
    std::cout << "\nВаш выбор: ";

    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (choice == 1) {
        std::string username, password;
        std::cout << "\nВведите имя пользователя: ";
        std::getline(std::cin, username);
        std::cout << "Введите пароль: ";
        std::getline(std::cin, password);
        RegularUser user(username, password);
        std::cout << "\nСоздан объект RegularUser:" << std::endl;
        std::cout << "Имя: " << user.getUsername() << std::endl;
        std::cout << "Роль: " << user.getRole() << std::endl;
    } else if (choice == 2) {
        std::string username, password;
        std::cout << "\nВведите имя администратора: ";
        std::getline(std::cin, username);
        std::cout << "Введите пароль: ";
        std::getline(std::cin, password);
        Administrator admin(username, password);
        std::cout << "\nСоздан объект Administrator:" << std::endl;
        std::cout << "Имя: " << admin.getUsername() << std::endl;
        std::cout << "Роль: " << admin.getRole() << std::endl;
    } else {
        std::cout << "\nНеверный выбор. Попробуйте снова." << std::endl;
    }
    std::cout << "\nНажмите Enter для продолжения...";
    std::cin.get();
}

PolymorphismDemoMenuItem::PolymorphismDemoMenuItem() 
    : MenuItem("Демонстрация полиморфизма", 10) { }

void PolymorphismDemoMenuItem::execute() {
    std::cout << "=== Демонстрация полиморфизма ===\n" << std::endl;
    
    MyVector<std::shared_ptr<User>> users;

    {
        std::string username, password;
        std::cout << "Создание объекта RegularUser:" << std::endl;
        std::cout << "Введите имя пользователя: ";
        std::getline(std::cin, username);
        std::cout << "Введите пароль: ";
        std::getline(std::cin, password);
        users.push_back(std::make_shared<RegularUser>(username, password));
    }
    
    std::cout << std::endl;

    {
        std::string username, password;
        std::cout << "Создание объекта Administrator:" << std::endl;
        std::cout << "Введите имя администратора: ";
        std::getline(std::cin, username);
        std::cout << "Введите пароль: ";
        std::getline(std::cin, password);
        users.push_back(std::make_shared<Administrator>(username, password));
    }

    std::cout << "\nРезультаты создания объектов:" << std::endl;
    
    for (size_t i = 0; i < users.size(); ++i) {
        std::cout << "\nОбъект " << (i + 1) << ":" << std::endl;
        std::cout << "Имя: " << users[i]->getUsername() << std::endl;
        std::cout << "Роль: " << users[i]->getRole() << std::endl;
        std::cout << "Администратор: " << (users[i]->isAdmin() ? "Да" : "Нет") << std::endl;
    }
    
    std::cout << "\nНажмите Enter для продолжения...";
    std::cin.get();
}