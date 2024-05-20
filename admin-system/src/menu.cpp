//
// Created by 15928 on 2022/5/3.
//
#include "../include/menu.h"
#include <iomanip>
void Menu::displayMainMenu() {
    std::cout << std::setw(20) << std::setfill('-') << "-" << std::endl;
    std::cout << "机房收费管理系统" << std::endl;
    std::cout << "请选择所需操作" << std::endl;
    std::cout << "1: 维护学生信息" << std::endl;
    std::cout << "2: 查询学生信息" << std::endl;
    std::cout << "3: 展示学生信息" << std::endl;
    std::cout << "4: 排序学生信息" << std::endl;
    std::cout << "5: 显示机器使用情况" << std::endl;
    std::cout << "0: 退出系统" << std::endl;
    std::cout << ">";
}
void Menu::displayMaintainMenu() {
    std::cout << std::setw(20) << std::setfill('-') << "-" << std::endl;
    std::cout << "请输入对应功能前的编号来操作上机管理系统" << std::endl
              << "1: 添加学生上机信息" << std::endl
              << "2: 添加学生下机信息" << std::endl
              << "3: 修改学生上机信息" << std::endl
              << "4: 删除学上上机信息" << std::endl
              << "0: 返回上级菜单" << std::endl;
    std::cout << ">";
}

void Menu::displayFetchMenu() {
    std::cout << std::setw(20) << std::setfill('-') << "-" << std::endl;
    std::cout << "请输入对应功能前的编号来查询信息" << std::endl
              << "1: 根据姓名学号进行精确查询" << std::endl
              << "2: 根据姓名进行精确查询" << std::endl
              << "0: 返回上级菜单" << std::endl;
    std::cout << ">";
}

void Menu::displayChangeMenu() {
    std::cout << std::setw(20) << std::setfill('-') << "-" << std::endl;
    std::cout << "请输入对应功能前的编号来修改信息" << std::endl
              << "1: 根据学号进行修改信息" << std::endl
              << "2: 根据姓名进行修改信息" << std::endl
              << "0: 返回上级菜单" << std::endl;
    std::cout << ">";
}

void Menu::displayDeleteMenu() {
    std::cout << std::setw(20) << std::setfill('-') << "-" << std::endl;
    std::cout << "请输入对应功能前的编号来删除用户" << std::endl
              << "1: 根据学号进行删除" << std::endl
              << "2: 根据姓名进行删除" << std::endl
              << "0: 返回上级菜单" << std::endl;
    std::cout << ">";
}

// void displayHeader() {
//     std::cout << std::setfill(' ') << std::setw(10) << "学号" <<
//     std::setw(10)
//               << "姓名" << std::setw(10) << "班级" << std::setw(10)
//               << "机器编号" << std::setw(10) << "上机开始时间" <<
//               std::setw(10)
//               << "上机结束时间" << std::setw(10) << "上机时长" <<
//               std::setw(10)
//               << "费用 /元" << std::endl;
// }

void displayHeader() {
    std::cout << std::left << std::setfill(' ') << "|" << std::setw(15)
              << "Num." << "|" << std::setw(10) << "Name" << "|"
              << std::setw(10) << "Class" << "|" << std::setw(15)
              << "MachineNum" << "|" << std::setw(10) << "BeginTime" << "|"
              << std::setw(10) << "EndTime" << "|" << std::setw(10) << "Length"
              << "|" << std::setw(15) << "Cost /yuan" << "|" << std::endl;
}
