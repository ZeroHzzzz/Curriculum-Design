//
// Created by 15928 on 2022/5/3.
//

#include "../include/file_manager.h"
#include <sstream>
#include "../include/machine.h"
#include "../include/menu.h"
#include "../include/userList.h"
File::File(const std::string path, const std::string fileType) {
    File::path = path;
    File::fileType = fileType;
}

void File::init(UserList& userList) {
    std::ifstream in;
    in.open(path + fileType, std::ios::in);
    if (!in.is_open()) {
        std::ofstream out;
        out.open(path + fileType, std::ios::out | std::ios::app);
        out.close();
        in.open(path + fileType, std::ios::in);
    }
    if (!in.is_open()) {
        std::cerr << "无法打开data.txt " << path + fileType << std::endl;
        return;
    }
    std::string line;
    while (std::getline(in, line)) {
        std::istringstream iss(line);
        userList.addNode(iss);
    }
    // userList.display();
    in.close();
    std::cout << "data初始化成功！" << std::endl;
}

void File::add(Info& user) {
    std::ofstream out;
    out.open(path + fileType, std::ios::app);
    if (!out.is_open()) {
        std::cout << "data.tct文件打开失败" << std::endl;
        return;
    }
    out << user << std::endl;
    out.close();
    mp.changeMachineStatus(user.getMachineNum(), user.getNum());
    std::cout << "信息添加成功:" << std::endl;
    displayHeader();
    std::cout << user << std::endl;
}

void File::change(UserList& userList) {
    std::ofstream out;
    out.open(path + ".temp", std::ios::app);
    if (!out.is_open()) {
        std::cout << "data.txt文件打开失败" << std::endl;
        return;
    }
    auto ptr = userList.getHead();
    if (ptr) {
        out << ptr->getData();
        ptr = ptr->getNext();
    }
    while (ptr) {
        out << ptr->getData();
        ptr = ptr->getNext();
    }
    out.close();
    remove((path + fileType).c_str());
    rename((path + ".temp").c_str(), (path + fileType).c_str());
}
