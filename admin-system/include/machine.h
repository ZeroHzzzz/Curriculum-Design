// MachineMap.h

#ifndef MACHINEMAP_H
#define MACHINEMAP_H

#include <map>
#include <string>
#include "student.h"
class MachineMap {
   public:
    // 更新机器使用状态
    MachineMap(const std::string, const std::string);
    void init();
    void changeMachineStatus(std::string, std::string);
    void updateMachineStatus(Info&, Info&);
    bool isMachineFree(const std::string&);
    // 保存到文件
    void saveToFile();
    void displayMap();

   private:
    std::map<std::string, std::string>
        machineStatus;  // 机器编号到使用状态的映射
    std::string fileType;
    std::string path;
};
extern MachineMap mp;
#endif
