#include "ChatBot.h"
#include <iostream>
#include <exception>

int main() {
    try {
        ChatBot bot;
        bot.run();
    } catch (const std::exception& ex) {
        std::cerr << "Критическая ошибка: " << ex.what() << "\n";
        return 1;
    }
    return 0;
}
