#include "ChatBot.h"
#include "MainMenu.h"
#include "Menu.h"
#include "MenuItem.h"
#include "ClearScreen.h"
#include <iostream>
#include <limits>
#include <cstdlib>
#include <string>

void ChatBot::run() {
    do {
        switchUserRequested = false;
        currentUser = auth.authenticate();
        if (!currentUser) {
            std::cout << "До свидания!\n";
            return;
        }

        MainMenu menu(currentUser);
        menu.addItem(new MenuItem("Начать диалог",       [&]{ startChat();        }));
        menu.addItem(new MenuItem("История сообщений",   [&]{ showHistory();      }));
        menu.addItem(new MenuItem("Изменить профиль",    [&]{ editProfile();      }));
        menu.addItem(new MenuItem("Сменить пользователя",[&]{ 
            switchUserRequested = true; 
            menu.requestExit(); 
        }));
        if (currentUser->isAdmin()) {
            menu.addItem(new MenuItem("Управление юзерами", [&]{ userManagement();   }));
            menu.addItem(new MenuItem("Статистика",         [&]{ showStatistics();   }));
        }
        menu.addItem(new MenuItem("Выход из программы",  [&]{ std::exit(0);        }));

        menu.display();
    } while (switchUserRequested);
}

void ChatBot::startChat() {
    clearScreen();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string line;
    std::cout << "=== Начало диалога (введите /exit) ===\n";
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, line);
        if (line == "/exit") break;
        history.push_back("You: " + line);
        std::cout << "Bot: " << line << "\n";
        history.push_back("Bot: " + line);
    }
    std::cout << "Диалог завершён. Нажмите Enter...";
    std::cin.get();
}

void ChatBot::showHistory() {
    clearScreen();
    std::cout << "=== История сообщений ===\n\n";
    if (history.empty()) {
        std::cout << "(пусто)\n";
    } else {
        for (size_t i = 0; i < history.size(); ++i) {
            std::cout << history[i] << "\n";
        }
    }
    std::cout << "\nНажмите Enter...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void ChatBot::editProfile() {
    clearScreen();
    const std::string oldUsername = currentUser->getUsername();
    const bool wasAdmin = currentUser->isAdmin();

    std::string newUsername, newPassword;
    std::cout << "=== Изменение профиля ===\n";
    std::cout << "Текущий логин: " << oldUsername << "\n";
    std::cout << "Новый логин (Enter, чтобы не менять): ";
    std::getline(std::cin, newUsername);
    std::cout << "Новый пароль (Enter, чтобы не менять): ";
    std::getline(std::cin, newPassword);

    if (newUsername.empty() && newPassword.empty()) {
        std::cout << "Ничего не изменено. Нажмите Enter...";
        std::cin.get();
        return;
    }

    const std::string finalUsername = newUsername.empty() ? oldUsername : newUsername;
    auth.deleteUser(oldUsername);

    if (newPassword.empty()) {
        const std::string oldHash = currentUser->getPasswordHash();
        auth.registerUser(finalUsername, oldHash, /*isRaw=*/false, wasAdmin);
    } else {
        auth.registerUser(finalUsername, newPassword, /*isRaw=*/true, wasAdmin);
    }

    currentUser = auth.getUser(finalUsername);
    auth.saveUsers();

    std::cout << "\nПрофиль обновлён. Нажмите Enter...";
    std::cin.get();
}

void ChatBot::userManagement() {
    while (true) {
        clearScreen();
        auto users = auth.getAllUsers();

        int adminCount = 0;
        for (auto u : users) {
            if (u->isAdmin()) {
                ++adminCount;
            }
        }

        std::cout << "=== Управление пользователями ===\n\n";

        // Выводим список пользователей
        for (size_t i = 0; i < users.size(); ++i) {
            std::cout << (i + 1) << ") "
                      << users[i]->getUsername()
                      << " [" << users[i]->getRole() << "]\n";
        }

        std::cout << "\nA — добавить, D — удалить, Enter — назад: ";
        std::string cmd;
        std::getline(std::cin, cmd);

        // Если нажали просто Enter — выходим из управления и остаёмся в главном меню
        if (cmd.empty()) {
            break;
        }

        if (cmd == "A" || cmd == "a") {
            // Добавление нового пользователя
            std::string lg, pw;
            std::cout << "=== Добавление пользователя ===\n";
            std::cout << "Логин (Enter для отмены): ";
            std::getline(std::cin, lg);
            if (lg.empty()) {
                // Отмена добавления — возвращаемся к списку
                continue;
            }
            std::cout << "Пароль (Enter для отмены): ";
            std::getline(std::cin, pw);
            if (pw.empty()) {
                // Отмена добавления — возвращаемся к списку
                continue;
            }

            if (auth.registerUser(lg, pw, /*isRaw=*/true, /*asAdmin=*/false)) {
                std::cout << "Пользователь добавлен.\n";
            } else {
                std::cout << "Ошибка: логин пуст или уже существует.\n";
            }
            std::cout << "\nНажмите Enter...";
            std::cin.get();
        }
        else if (cmd == "D" || cmd == "d") {
            // Удаление пользователя
            if (users.empty()) {
                std::cout << "Список пользователей пуст.\n";
                std::cout << "\nНажмите Enter...";
                std::cin.get();
                continue;
            }

            std::cout << "=== Удаление пользователя ===\n";
            std::cout << "Введите номер для удаления (Enter для отмены): ";

            std::string s;
            std::getline(std::cin, s);
            if (s.empty()) {
                // Отмена удаления — возвращаемся к списку
                continue;
            }

            int idx = 0;
            try {
                idx = std::stoi(s);
            } catch (...) {
                idx = 0;
            }
            if (idx < 1 || idx > static_cast<int>(users.size())) {
                std::cout << "Неверный номер.\n";
                std::cout << "\nНажмите Enter...";
                std::cin.get();
                continue;
            }

            User* target = users[idx - 1];
            if (target->isAdmin() && target != currentUser) {
                std::cout << "Нельзя удалить другого администратора.\n";
            }
            else if (target == currentUser && target->isAdmin() && adminCount <= 1) {
                std::cout << "Вы единственный админ.\n";
            }
            else {
                auth.deleteUser(target->getUsername());
                std::cout << "Пользователь удалён.\n";
                if (target == currentUser) {
                    std::cout << "Вы удалили себя. Выходим.\n";
                    std::exit(0);
                }
            }

            std::cout << "\nНажмите Enter...";
            std::cin.get();
        }
        else {
            // Неверная команда — просто покажем меню снова
            continue;
        }
    }
}

void ChatBot::showStatistics() {
    clearScreen();
    std::cout << "=== Статистика ===\n\n";
    std::cout << "Сообщений: " << history.size() << "\n";
    std::cout << "Пользователей: " << auth.getAllUsers().size() << "\n\n";
    std::cout << "Нажмите Enter...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
