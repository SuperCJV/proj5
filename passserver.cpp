#include <iostream>
#include <fstream>
#include <cstring>
#include "passserver.h"
#include <unistd.h> // For crypt()

PassServer::PassServer(size_t size) : table(size) {}

PassServer::~PassServer() {
    table.clear();
}

bool PassServer::load(const char *filename) {
    return table.load(filename);
}

bool PassServer::addUser(std::pair<std::string, std::string> &kv) {
    kv.second = encrypt(kv.second);
    return table.insert(kv);
}

bool PassServer::addUser(std::pair<std::string, std::string> &&kv) {
    kv.second = encrypt(kv.second);
    return table.insert(std::move(kv));
}

bool PassServer::removeUser(const std::string &k) {
    return table.remove(k);
}

bool PassServer::changePassword(const std::pair<std::string, std::string> &p, const std::string &newpassword) {
    if (newpassword == p.second) return false; // New password same as old password

    auto encryptedOldPassword = encrypt(p.second);
    auto encryptedNewPassword = encrypt(newpassword);

    if (!table.match({p.first, encryptedOldPassword})) return false; // Old password mismatch

    return table.insert({p.first, encryptedNewPassword}); // Update password
}

bool PassServer::find(const std::string &user) const {
    return table.contains(user);
}

void PassServer::dump() const {
    table.dump();
}

size_t PassServer::size() const {
    return table.size();
}

bool PassServer::write_to_file(const char *filename) const {
    return table.write_to_file(filename);
}

std::string PassServer::encrypt(const std::string &str) {
    const char *salt = "$1$########";
    char *encrypted = crypt(str.c_str(), salt);
    if (!encrypted) {
        throw std::runtime_error("Encryption failed");
    }

    std::string result(encrypted);
    auto pos = result.find_last_of('$');
    if (pos == std::string::npos || pos + 1 >= result.size()) {
        throw std::runtime_error("Unexpected encryption format");
    }

    return result.substr(pos + 1);
}