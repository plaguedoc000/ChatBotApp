#include "MenuItem.h"

MenuItem::MenuItem(const std::string& label_, std::function<void()> action_)
    : label(label_), action(std::move(action_))
{}

std::string MenuItem::getLabel() const {
    return label;
}

void MenuItem::execute() {
    action();
}
