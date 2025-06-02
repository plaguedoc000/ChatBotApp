#ifndef CHATBOT_CHATBOT_H
#define CHATBOT_CHATBOT_H

#include "AuthSystem.h"
#include "MyVector.h"
#include <string>

class ChatBot {
private:
    AuthSystem auth;
    User* currentUser = nullptr;
    bool switchUserRequested = false;
    MyVector<std::string> history;

    void startChat();
    void showHistory();
    void editProfile();
    void userManagement();
    void showStatistics();

public:
    ChatBot() = default;
    void run();
};

#endif // CHATBOT_CHATBOT_H
