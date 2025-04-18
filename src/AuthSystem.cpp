#include "AuthSystem.h"
#include <iostream>
#include <limits>

AuthSystem::AuthSystem() {
    // Добавляем нескольких предустановленных пользователей
    users["user"] = new RegularUser("user", "pass");
    users["admin"] = new Administrator("admin", "admin");
}

AuthSystem::~AuthSystem() {
    // Освобождаем память, занимаемую пользователями
    for (auto& pair : users) {
        delete pair.second;
    }
    users.clear();
}

User* AuthSystem::authenticate() {
    std::string username, password;
    
    while (true) {
        system("cls"); // Очистка экрана (для Windows)
        // system("clear"); // Для Linux/MacOS
        
        std::cout << "=== Авторизация ===\n" << std::endl;
        std::cout << "Логин: ";
        std::cin >> username;
        
        std::cout << "Пароль: ";
        std::cin >> password;
        
        auto userIt = users.find(username);
        
        if (userIt != users.end() && userIt->second->checkPassword(password)) {
            std::cout << "Авторизация успешна! Добро пожаловать, " 
                      << userIt->second->getUsername() << "!" << std::endl;
            std::cout << "Нажмите Enter для продолжения...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            return userIt->second;
        } else {
            std::cout << "Неверный логин или пароль." << std::endl;
            std::cout << "Нажмите Enter для повторной попытки...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }
    }
}