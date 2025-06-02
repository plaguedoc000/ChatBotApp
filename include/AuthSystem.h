#ifndef CHATBOT_AUTH_SYSTEM_H
#define CHATBOT_AUTH_SYSTEM_H

#include "User.h"
#include "MyVector.h"
#include <map>
#include <string>

static constexpr const char* USERS_FILE = "users.txt";

class AuthSystem {
private:
    std::map<std::string, User*> users;

    void loadUsers();

public:
    AuthSystem();
    ~AuthSystem();

    void saveUsers() const;

    User* authenticate();

    // Если isRawPasswordOrHash==true, то passwordOrHash трактуется как «сырой» пароль,
    // иначе как уже готовый хэш.
    bool registerUser(const std::string& login,
                      const std::string& passwordOrHash,
                      bool isRawPasswordOrHash = true,
                      bool asAdmin = false);

    bool deleteUser(const std::string& login);

    User* getUser(const std::string& login) const;

    MyVector<User*> getAllUsers() const;
};

#endif // CHATBOT_AUTH_SYSTEM_H
