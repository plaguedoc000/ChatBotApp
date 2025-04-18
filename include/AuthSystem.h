#ifndef CHATBOT_AUTH_SYSTEM_H
#define CHATBOT_AUTH_SYSTEM_H

#include <map>
#include <memory>
#include <string>
#include "User.h"

// Класс для хранения пользователей и их авторизации
class AuthSystem {
private:
    std::map<std::string, User*> users; 

public:
    AuthSystem();
    ~AuthSystem();

    User* authenticate();
};

#endif // CHATBOT_AUTH_SYSTEM_H