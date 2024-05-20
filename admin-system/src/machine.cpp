// MachineMap.cpp

#include "../include/machine.h"
#include <fstream>
#include <iostream>
#include <sstream>
// 更新机器使用状态
MachineMap mp("../data/machines", ".txt");

MachineMap::MachineMap(const std::string path, const std::string fileType) {
    MachineMap::path = path;
    MachineMap::fileType = fileType;
}

void MachineMap::init() {
    std::ifstream in;
    in.open(path + fileType, std::ios::in);
    if (!in.is_open()) {
        std::ofstream out;
        out.open(path + fileType, std::ios::out | std::ios::app);
        out.close();
        in.open(path + fileType, std::ios::in);
    }
    if (!in.is_open()) {
        std::cerr << "无法打开machines.txt: " << path + fileType << std::endl;
        return;
    }
    std::string line;
    while (std::getline(in, line)) {
        std::istringstream iss(line);
        std::string machineNumber;
        std::string userName;
        if (std::getline(iss, machineNumber, ':') &&
            std::getline(iss, userName)) {
            machineStatus[machineNumber] = userName;
        }
    }
    in.close();
    std::cout << "machines初始化成功！" << std::endl;
}

void MachineMap::changeMachineStatus(std::string machineNumber,
                                     std::string userNum) {
    machineStatus[machineNumber] = userNum;
    saveToFile();
}

void MachineMap::updateMachineStatus(Info& former, Info& latter) {
    machineStatus[former.getMachineNum()] = "FREE";
    machineStatus[latter.getMachineNum()] = latter.getNum();
    saveToFile();
}

// 保存到文件
void MachineMap::saveToFile() {
    std::ofstream out;
    out.open(path + fileType, std::ios::out);
    if (!out.is_open()) {
        std::cout << "machines.txt打开失败" << std::endl;
        return;
    }
    for (const auto& pair : mp.machineStatus) {
        out << pair.first << ":" << pair.second << std::endl;
    }
    out.close();
    std::cout << "保存成功！" << std::endl;
}
void MachineMap::displayMap() {
    for (const auto& pair : machineStatus) {
        std::cout << pair.first << ":" << pair.second << std::endl;
    }
}
bool MachineMap::isMachineFree(const std::string& machineNumber) {
    auto it = machineStatus.find(machineNumber);
    if (it != machineStatus.end() && it->second == "FREE") {
        return true;
    }
    return false;
}
