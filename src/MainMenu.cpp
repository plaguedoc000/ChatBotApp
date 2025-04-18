#include "MainMenu.h"

MainMenu::MainMenu(User* user)
    : Menu("Главное меню - " + user->getRole()), currentUser(user) {}

MainMenu::~MainMenu() {
    // Мы не удаляем currentUser здесь, так как его жизненным циклом управляет AuthSystem
}