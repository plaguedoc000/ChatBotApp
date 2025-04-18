#include "Menu.h"
#include <iostream>
#include <limits>

Menu::Menu(const std::string& title) : title(title) {}

Menu::~Menu() {
    // Освобождаем память, занимаемую пунктами меню
    for (MenuItem* item : items) {
        delete item;
    }
    items.clear();
}

void Menu::addItem(MenuItem* item) {
    items.push_back(item);
}

void Menu::display() {
    while (!exitRequested) {
        system("cls"); // Очистка экрана (для Windows)
        // system("clear"); // Для Linux/MacOS

        std::cout << "\n=== " << title << " ===\n" << std::endl;
        
        for (size_t i = 0; i < items.size(); ++i) {
            std::cout << (i + 1) << ". " << items[i]->getTitle() << std::endl;
        }
        
        std::cout << "\nВыберите опцию (1-" << items.size() << "): ";
        
        int choice;
        std::cin >> choice;
        
        // Очистка буфера ввода
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if (choice > 0 && static_cast<size_t>(choice) <= items.size()) {
            items[choice - 1]->execute();
        } else {
            std::cout << "Неверный выбор. Пожалуйста, попробуйте снова." << std::endl;
            std::cout << "Нажмите Enter для продолжения...";
            std::cin.get();
        }
    }
}

void Menu::requestExit() {
    exitRequested = true;
}