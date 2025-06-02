#ifndef CHATBOT_MENU_ITEM_H
#define CHATBOT_MENU_ITEM_H

#include <string>
#include <functional>

class MenuItem {
private:
    std::string label;
    std::function<void()> action;

public:
    MenuItem(const std::string& label, std::function<void()> action);
    ~MenuItem() = default;

    std::string getLabel() const;
    void execute();
};

#endif // CHATBOT_MENU_ITEM_H
