#ifndef LOGINSYSTEM_H
#define LOGINSYSTEM_H

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

class LoginSystem {
   private:
    std::unordered_map<std::string, std::string> users;
    void loadUsersFromFile(const std::string& filename);

   public:
    LoginSystem(const std::string& filename);
    bool login();
};

#endif  // LOGINSYSTEM_H
