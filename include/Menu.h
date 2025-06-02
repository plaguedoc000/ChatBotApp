#ifndef CHATBOT_MENU_H
#define CHATBOT_MENU_H

#include "MenuItem.h"
#include "MyVector.h"
#include <string>

class Menu {
protected:
    std::string title;
    MyVector<MenuItem*> items;
    bool exitRequested = false;

public:
    Menu(const std::string& title);
    virtual ~Menu();

    void addItem(MenuItem* item);
    void display();
    void requestExit();
};

#endif // CHATBOT_MENU_H
