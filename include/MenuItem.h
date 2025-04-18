#ifndef CHATBOT_MENU_ITEM_H
#define CHATBOT_MENU_ITEM_H

#include <string>

// Определение класса MenuItem (пункт меню)
class MenuItem {
private:
    std::string title;
    int id;

public:
    MenuItem(const std::string& title, int id);
    virtual ~MenuItem() = default;

    std::string getTitle() const;
    int getId() const;
    virtual void execute();
};

#endif // CHATBOT_MENU_ITEM_H