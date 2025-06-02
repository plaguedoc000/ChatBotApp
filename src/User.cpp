#include "User.h"
#include <sstream>

// Хеширование через std::hash
std::string User::hashPassword(const std::string& raw) {
    auto h = std::hash<std::string>{}(raw);
    std::ostringstream oss;
    oss << h;
    return oss.str();
}

User::User(const std::string& username_, const std::string& rawPassword)
    : username(username_), passwordHash(hashPassword(rawPassword))
{}

User::User(const std::string& username_,
           const std::string& passwordOrHash,
           bool isRawHash)
    : username(username_)
{
    if (isRawHash) {
        passwordHash = hashPassword(passwordOrHash);
    } else {
        passwordHash = passwordOrHash;
    }
}

std::string User::getUsername() const {
    return username;
}

std::string User::getPasswordHash() const {
    return passwordHash;
}

bool User::checkPassword(const std::string& rawPassword) const {
    return hashPassword(rawPassword) == passwordHash;
}

void User::setPassword(const std::string& rawPassword) {
    passwordHash = hashPassword(rawPassword);
}

std::string User::getRole() const {
    return "User";
}

bool User::isAdmin() const {
    return false;
}

// --- Перегрузка operator== / operator!= для User ---
bool User::operator==(const User& other) const {
    return username == other.username
        && passwordHash == other.passwordHash
        && getRole() == other.getRole();
}

bool User::operator!=(const User& other) const {
    return !(*this == other);
}

// --- Перегрузка operator<< для User ---
std::ostream& operator<<(std::ostream& os, const User& u) {
    os << u.getUsername() << " [" << u.getRole() << "]";
    return os;
}

// ---------------------------------------------------
// RegularUser
RegularUser::RegularUser(const std::string& username_, const std::string& rawPassword)
    : User(username_, rawPassword)
{}

RegularUser::RegularUser(const std::string& username_,
                         const std::string& passwordOrHash,
                         bool isRawHash)
    : User(username_, passwordOrHash, isRawHash)
{}

std::string RegularUser::getRole() const {
    return "Regular User";
}

// ---------------------------------------------------
// Administrator
Administrator::Administrator(const std::string& username_, const std::string& rawPassword)
    : User(username_, rawPassword)
{}

Administrator::Administrator(const std::string& username_,
                             const std::string& passwordOrHash,
                             bool isRawHash)
    : User(username_, passwordOrHash, isRawHash)
{}

std::string Administrator::getRole() const {
    return "Administrator";
}

bool Administrator::isAdmin() const {
    return true;
}
