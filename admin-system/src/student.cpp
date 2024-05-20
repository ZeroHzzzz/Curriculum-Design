#include "../include/student.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <regex>
#include <utility>
#include "../include/machine.h"
// 这个函数可以不放到类的实现中
int parseTimeToMinutes(const std::string& timeStr) {
    int hours, minutes;
    std::stringstream ss(timeStr);
    char colon;
    ss >> hours >> colon >> minutes;
    return hours * 60 + minutes;
}

int getMinuteDifference(const std::string& time1, const std::string& time2) {
    int minutes1 = parseTimeToMinutes(time1);
    int minutes2 = parseTimeToMinutes(time2);
    return std::abs(minutes2 - minutes1);  // 返回绝对值，确保得到的是正数
}

Info::Info() = default;
Info::~Info() = default;
const std::string& Info::getName() const {
    return name;
}
const std::string& Info::getNum() const {
    return num;
}
const std::string& Info::getClassName() const {
    return className;
}
const std::string& Info::getMachineNum() const {
    return machineNum;
}
const std::string& Info::getBeginTime() const {
    return beginTime;
}
const std::string& Info::getEndTime() const {
    return endTime;
}
const int& Info::getTotalTime() const {
    return totalTime;
}
const double& Info::getCost() const {
    return cost;
}

void Info::setName(const std::string& name) {
    Info::name = name;
}
void Info::setNum(const std::string& num) {
    Info::num = num;
}
void Info::setClassName(const std::string& className) {
    Info::className = className;
}
void Info::setMachineNum(const std::string& machineNum) {
    Info::machineNum = machineNum;
}
void Info::setBeginTime(const std::string& beginTime) {
    Info::beginTime = beginTime;
}
void Info::setEndTime(const std::string& endTime) {
    Info::endTime = endTime;
}

void Info::setTotalTime() {
    if (Info::beginTime == "-" || Info::endTime == "-")
        Info::totalTime = 0;
    else
        Info::totalTime = getMinuteDifference(beginTime, endTime);
}

void Info::calculateCost(const int& totalTime) {
    Info::cost = std::ceil(totalTime / 60.0) * 1;
}

std::istream& operator>>(std::istream& in, Info& right) {
    if (typeid(in) == typeid(std::cin)) {
        std::cout << "请输入该用户的学号：";
        in >> right.num;
        std::cout << "请输入该用户的姓名：";
        in >> right.name;
        std::cout << "请输入班级：";
        in >> right.className;
        std::cout << "请输入机器号码：";
        std::string machineNum;
        while (in >> machineNum) {
            if (mp.isMachineFree(machineNum) == true) {
                right.setMachineNum(machineNum);
                break;
            } else {
                std::cout << "该机器已被占用，请重新选择：";
            }
        }
        std::regex timePattern(R"(^([01][0-9]|2[0-3]):[0-5][0-9]$)");

        std::string begintime;
        std::cout << "请输入上机开始时间:";
        while (in >> begintime) {
            if (std::regex_match(begintime, timePattern)) {
                right.setBeginTime(begintime);
                break;
            } else {
                std::cout << "时间格式不正确，应为 HH:MM:(英文冒号)";
            }
        }
    } else {
        in >> right.num >> right.name >> right.className >> right.machineNum >>
            right.beginTime >> right.endTime >> right.totalTime >> right.cost;
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Info& right) {
    // out << std::left << std::setw(10) << "学号" << "姓名" << "班级"
    //     << "机器编号" << "上机开始时间" << "上机结束时间" << "上机时长"
    //     << "费用" << std::endl;
    if (typeid(out) == typeid(std::cout)) {
        out << std::setfill(' ') << "|" << std::setw(15) << right.getNum()
            << "|" << std::setw(10) << right.getName() << "|" << std::setw(10)
            << right.getClassName() << "|" << std::setw(15)
            << right.getMachineNum() << "|" << std::setw(10)
            << right.getBeginTime() << "|" << std::setw(10)
            << right.getEndTime() << "|" << std::setw(10)
            << right.getTotalTime() << "|" << std::setw(15) << right.getCost()
            << "|";
    } else {
        out << right.getNum() << " " << right.getName() << " "
            << right.getClassName() << " " << right.getMachineNum() << " "
            << right.getBeginTime() << " " << right.getEndTime() << " "
            << right.getTotalTime() << " " << right.getCost();
    }

    return out;
}
