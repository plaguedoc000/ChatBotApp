#ifndef CHATBOT_USER_H
#define CHATBOT_USER_H

#include <string>

// Определение класса User (базовый класс)
class User {
protected:
    std::string username;
    std::string password;

public:
    User(const std::string& username, const std::string& password);
    virtual ~User() = default;

    std::string getUsername() const;
    bool checkPassword(const std::string& inputPassword) const;
    virtual std::string getRole() const;
    virtual bool isAdmin() const;
};

// Определение класса RegularUser (наследник класса User)
class RegularUser : public User {
public:
    RegularUser(const std::string& username, const std::string& password);
    std::string getRole() const override;
};

// Определение класса Administrator (наследник класса User)
class Administrator : public User {
public:
    Administrator(const std::string& username, const std::string& password);
    std::string getRole() const override;
    bool isAdmin() const override;
};

#endif // CHATBOT_USER_H