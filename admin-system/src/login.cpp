#include "../include/login.h"
#include <sstream>
// 从文件中读取用户信息
void LoginSystem::loadUsersFromFile(const std::string& filename) {
    std::ifstream in;
    in.open(filename, std::ios::in);
    if (!in.is_open()) {
        std::ofstream out;
        out.open(filename, std::ios::out | std::ios::app);
        out.close();
        in.open(filename, std::ios::in);
    }
    if (!in.is_open()) {
        std::cerr << "无法打开" << filename << std::endl;
        return;
    }
    std::string line;
    while (std::getline(in, line)) {
        std::istringstream iss(line);
        std::string username, password;
        while (iss >> username >> password) {
            users[username] = password;
        }
    }
    // userList.display();
    in.close();
    std::cout << "用户数据初始化成功！" << std::endl;
}

// 构造函数
LoginSystem::LoginSystem(const std::string& filename) {
    loadUsersFromFile(filename);
}

// 检查用户登录
bool LoginSystem::login() {
    std::string username, password;
    std::cout << "请输入用户名: ";
    std::cin >> username;
    std::cout << "请输入密码: ";
    std::cin >> password;
    auto it = users.find(username);
    if (it != users.end() && it->second == password) {
        return true;
    }
    return false;
}
