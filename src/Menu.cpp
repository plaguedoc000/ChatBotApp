#include "Menu.h"
#include <iostream>
#include <limits>
#include "ClearScreen.h"

Menu::Menu(const std::string& title_) : title(title_) {}

Menu::~Menu() {
    for (auto item : items) {
        delete item;
    }
    items.clear();
}

void Menu::addItem(MenuItem* item) {
    items.push_back(item);
}

void Menu::display() {
    while (!exitRequested) {
        clearScreen();
        std::cout << "\n=== " << title << " ===\n\n";

        for (size_t i = 0; i < items.size(); ++i) {
            std::cout << (i + 1) << ". " << items[i]->getLabel() << "\n";
        }

        std::cout << "\nВыберите (1-" << items.size() << "): ";
        int choice;
        if (!(std::cin >> choice) ||
            choice < 1 || choice > (int)items.size()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        items[choice - 1]->execute();
    }
}

void Menu::requestExit() {
    exitRequested = true;
}
