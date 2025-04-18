#ifndef CHATBOT_CHATBOT_H
#define CHATBOT_CHATBOT_H

#include "AuthSystem.h"

// Главный класс чатбота
class ChatBot {
private:
    AuthSystem authSystem;

public:
    void run();
};

#endif // CHATBOT_CHATBOT_H