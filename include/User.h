#ifndef CHATBOT_USER_H
#define CHATBOT_USER_H

#include <string>
#include <functional>
#include <ostream>

class User {
protected:
    std::string username;
    std::string passwordHash;

    static std::string hashPassword(const std::string& raw);

public:
    User(const std::string& username, const std::string& rawPassword);
    User(const std::string& username,
         const std::string& passwordOrHash,
         bool isRawHash);

    virtual ~User() = default;

    std::string getUsername() const;
    std::string getPasswordHash() const;

    bool checkPassword(const std::string& rawPassword) const;
    void setPassword(const std::string& rawPassword);

    virtual std::string getRole() const;
    virtual bool isAdmin() const;

    // Перегрузка операторов для User
    bool operator==(const User& other) const;
    bool operator!=(const User& other) const;

    friend std::ostream& operator<<(std::ostream& os, const User& u);
};

class RegularUser : public User {
public:
    RegularUser(const std::string& username, const std::string& rawPassword);
    RegularUser(const std::string& username,
                const std::string& passwordOrHash,
                bool isRawHash);

    std::string getRole() const override;
};

class Administrator : public User {
public:
    Administrator(const std::string& username, const std::string& rawPassword);
    Administrator(const std::string& username,
                  const std::string& passwordOrHash,
                  bool isRawHash);

    std::string getRole() const override;
    bool isAdmin() const override;
};

#endif // CHATBOT_USER_H
