#include "AuthSystem.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include "ClearScreen.h"
#include <limits>

// Загрузка всех пользователей из файла
void AuthSystem::loadUsers() {
    std::ifstream in(USERS_FILE);
    if (!in.is_open())
        throw std::runtime_error("Не удалось открыть " + std::string(USERS_FILE));

    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        auto p1 = line.find(':');
        auto p2 = line.rfind(':');
        if (p1 == std::string::npos || p2 == std::string::npos || p1 == p2) {
            std::cerr << "[AuthSystem] пропущена строка: " << line << "\n";
            continue;
        }
        std::string login = line.substr(0, p1);
        std::string hash  = line.substr(p1 + 1, p2 - p1 - 1);
        std::string role  = line.substr(p2 + 1);

        if (role == "admin") {
            users[login] = new Administrator(login, hash, /*isRawHash=*/false);
        } else {
            users[login] = new RegularUser(login, hash, /*isRawHash=*/false);
        }
    }
    in.close();
}

AuthSystem::AuthSystem() {
    loadUsers();
    if (users.find("admin") == users.end()) {
        users["admin"] = new Administrator("admin", "admin");
        saveUsers();
    }
}

AuthSystem::~AuthSystem() {
    for (auto& kv : users) {
        delete kv.second;
    }
    users.clear();
}

// Запись всех пользователей в файл
void AuthSystem::saveUsers() const {
    std::ofstream out(USERS_FILE, std::ios::trunc);
    if (!out.is_open())
        throw std::runtime_error("Не удалось открыть для записи " + std::string(USERS_FILE));

    for (auto& kv : users) {
        const User& u = *kv.second;
        out << u.getUsername() << ":"
            << u.getPasswordHash() << ":"
            << (u.isAdmin() ? "admin" : "user")
            << "\n";
    }
    out.close();
}

// Меню «Авторизация / Регистрация / Выход»
User* AuthSystem::authenticate() {
    while (true) {
        clearScreen();
        std::cout << "=== Авторизация ===\n"
                  << "1) Вход\n"
                  << "2) Регистрация\n"
                  << "3) Выход\n"
                  << "Выберите: ";
        int choice;
        if (!(std::cin >> choice) || choice < 1 || choice > 3) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 3) {
            return nullptr;
        }
        if (choice == 2) {
            std::string login, pass;
            std::cout << "Новый логин: ";  std::getline(std::cin, login);
            if (login.empty() || users.count(login)) {
                std::cout << "Логин пуст или уже существует. Enter..."; std::cin.get();
                continue;
            }
            std::cout << "Пароль: ";      std::getline(std::cin, pass);
            if (pass.empty()) {
                std::cout << "Пароль не может быть пустым. Enter..."; std::cin.get();
                continue;
            }
            registerUser(login, pass, /*isRaw=*/true, /*asAdmin=*/false);
            std::cout << "Регистрация прошла успешно. Enter..."; std::cin.get();
            continue;
        }
        // Вход
        {
            std::string login, pass;
            std::cout << "Логин: ";  std::getline(std::cin, login);
            std::cout << "Пароль: "; std::getline(std::cin, pass);
            auto it = users.find(login);
            if (it != users.end() && it->second->checkPassword(pass)) {
                return it->second;
            }
            std::cout << "Неверный логин или пароль. Enter..."; std::cin.get();
        }
    }
}

// Регистрация нового пользователя или администратора
bool AuthSystem::registerUser(const std::string& login,
                              const std::string& passwordOrHash,
                              bool isRawPasswordOrHash,
                              bool asAdmin)
{
    if (login.empty() || passwordOrHash.empty() || users.count(login))
        return false;

    if (asAdmin) {
        users[login] = new Administrator(login, passwordOrHash, isRawPasswordOrHash);
    } else {
        users[login] = new RegularUser(login, passwordOrHash, isRawPasswordOrHash);
    }
    saveUsers();
    return true;
}

// Удаление пользователя
bool AuthSystem::deleteUser(const std::string& login) {
    auto it = users.find(login);
    if (it == users.end()) return false;
    delete it->second;
    users.erase(it);
    saveUsers();
    return true;
}

User* AuthSystem::getUser(const std::string& login) const {
    auto it = users.find(login);
    return (it == users.end() ? nullptr : it->second);
}

MyVector<User*> AuthSystem::getAllUsers() const {
    MyVector<User*> out;
    for (auto& kv : users) {
        out.push_back(kv.second);
    }
    return out;
}
