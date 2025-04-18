#include "User.h"

User::User(const std::string& username, const std::string& password)
    : username(username), password(password) {}

std::string User::getUsername() const {
    return username;
}

bool User::checkPassword(const std::string& inputPassword) const {
    return password == inputPassword;
}

std::string User::getRole() const {
    return "User";
}

bool User::isAdmin() const {
    return false;
}

RegularUser::RegularUser(const std::string& username, const std::string& password)
    : User(username, password) {}

std::string RegularUser::getRole() const {
    return "Regular User";
}

Administrator::Administrator(const std::string& username, const std::string& password)
    : User(username, password) {}

std::string Administrator::getRole() const {
    return "Administrator";
}

bool Administrator::isAdmin() const {
    return true;
}