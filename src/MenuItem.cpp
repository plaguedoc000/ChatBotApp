#include "MenuItem.h"
#include <iostream>
#include <limits>

MenuItem::MenuItem(const std::string& title, int id)
    : title(title), id(id) {}

std::string MenuItem::getTitle() const {
    return title;
}

int MenuItem::getId() const {
    return id;
}

void MenuItem::execute() {
    std::cout << "Выбранный пункт меню: " << title << std::endl;
    std::cout << "Этот функционал еще не реализован." << std::endl;
    std::cout << "Нажмите Enter для продолжения...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}