#include <iomanip>
#include <iostream>
#include "../include/file_manager.h"
#include "../include/machine.h"
#include "../include/menu.h"
int main() {
    Menu menu;
    UserList list;
    File file("../data/data", ".txt");
    file.init(list);
    mp.init();
    int userChoice = 0;
    menu.displayMainMenu();
    while (std::cin >> userChoice && userChoice) {
        switch (userChoice) {
            // 维护学生信息
            case 1: {
                menu.displayMaintainMenu();
                int typeNum = 0;
                while (std::cin >> typeNum && typeNum) {
                    switch (typeNum) {
                        // 添加上机信息
                        case 1: {
                            std::cout << std::setw(20) << std::setfill('-')
                                      << std::endl;
                            file.add(list.addNode(std::cin));
                            break;
                        }
                        // 添加下机信息
                        case 2: {
                            std::cout << std::setw(20) << std::setfill('-')
                                      << std::endl;
                            std::cout << "请输入想添加信息的学生的学号：";
                            std::string num;
                            std::cin >> num;
                            list.changeNode_info(num);
                            file.change(list);
                            break;
                        }
                        // 修改学生上机信息
                        case 3: {
                            if (!list.getSize()) {
                                std::cout << std::setw(20) << std::setfill('-')
                                          << "-" << std::endl;
                                std::cout << "当前链表为空" << std::endl;
                                break;
                            }
                            menu.displayChangeMenu();
                            int typeNum_ = 0;
                            bool flag = true;
                            while (flag && std::cin >> typeNum_ && typeNum_) {
                                switch (typeNum_) {
                                    case 0: {
                                        flag = false;
                                        break;
                                    }
                                    case 1: {
                                        std::cout << std::setw(20)
                                                  << std::setfill('-') << "-"
                                                  << std::endl;
                                        std::cout << "请输入想修改学生的学号：";
                                        std::string num;
                                        std::cin >> num;
                                        list.changeNode(num, "num");
                                        file.change(list);
                                        flag = false;
                                        break;
                                    }
                                    case 2: {
                                        std::cout << std::setw(20)
                                                  << std::setfill('-') << "-"
                                                  << std::endl;
                                        std::cout << "请输入想修改用户的姓名：";
                                        std::string name;
                                        std::cin >> name;
                                        list.changeNode(name, "name");
                                        file.change(list);
                                        flag = false;
                                        break;
                                    }
                                    default: {
                                        std::cout << "输入有误，请重新输入\n";
                                        break;
                                    }
                                }
                                if (typeNum_)
                                    menu.displayChangeMenu();
                            }
                            break;
                        }
                        // 删除学生上机信息
                        case 4: {
                            if (!list.getSize()) {
                                std::cout << std::setw(20) << std::setfill('-')
                                          << "-" << std::endl;
                                std::cout << "当前链表为空" << std::endl;
                                break;
                            }
                            menu.displayDeleteMenu();
                            int typeNum_;
                            bool flag = true;
                            while (flag && std::cin >> typeNum_ && typeNum_) {
                                switch (typeNum_) {
                                    case 0: {
                                        flag = false;
                                        break;
                                    }
                                    case 1: {
                                        std::cout << std::setw(20)
                                                  << std::setfill('-') << "-"
                                                  << std::endl;
                                        list.display();
                                        std::cout << "请输入想删除用户的学号：";
                                        std::string num;
                                        std::cin >> num;
                                        // list.fetchNode()
                                        auto user = list.fetchNode(num, "num");
                                        if (user) {
                                            displayHeader();
                                            std::cout << *user;
                                            std::cout << "确认删除?(y/n):";
                                            char choice = 'n';
                                            while (std::cin >> choice) {
                                                if (choice == 'y') {
                                                    mp.changeMachineStatus(
                                                        user->getData()
                                                            .getMachineNum(),
                                                        "FREE");
                                                    list.delNode(num, "num");
                                                    file.change(list);
                                                    break;
                                                } else if (choice == 'n') {
                                                    break;
                                                }
                                            }
                                            break;
                                        } else {
                                            std::cout << "该用户不存在"
                                                      << std::endl;
                                            break;
                                        }
                                        break;
                                    }
                                    case 2: {
                                        std::cout << std::setw(20)
                                                  << std::setfill('-') << "-"
                                                  << std::endl;
                                        list.display();
                                        std::cout << "请输入想删除用户的姓名：";
                                        std::string name;
                                        std::cin >> name;
                                        auto user =
                                            list.fetchNode(name, "name");
                                        if (user) {
                                            displayHeader();
                                            std::cout << *user;
                                            std::cout << "确认删除?(y/n):";
                                            char choice = 'n';
                                            while (std::cin >> choice) {
                                                if (choice == 'y') {
                                                    mp.changeMachineStatus(
                                                        user->getData()
                                                            .getMachineNum(),
                                                        "FREE");
                                                    list.delNode(name, "name");
                                                    file.change(list);
                                                    break;
                                                } else if (choice == 'n') {
                                                    break;
                                                }
                                            }
                                            break;
                                        } else {
                                            std::cout << "该用户不存在"
                                                      << std::endl;
                                            break;
                                        }
                                        break;
                                    }
                                    default: {
                                        std::cout << "输入有误，请重新输入\n";
                                        break;
                                    }
                                }
                                if (typeNum_)
                                    menu.displayDeleteMenu();
                            }
                            break;
                        }
                        default: {
                            std::cout << "输入有误，请重新输入\n";
                        }
                    }
                    if (typeNum)
                        menu.displayMaintainMenu();
                }
                break;
            }
            // 查询学生信息
            case 2: {
                if (!list.getSize()) {
                    std::cout << "当前链表为空" << std::endl;
                    break;
                }
                menu.displayFetchMenu();
                int typeNum_;
                bool flag = true;
                while (flag && std::cin >> typeNum_ && typeNum_) {
                    switch (typeNum_) {
                        case 0: {
                            flag = false;
                            break;
                        }
                        case 1: {
                            std::cout << "请输入想查询用户的学号：";
                            std::string num;
                            std::cin >> num;
                            auto user = list.fetchNode(num, "num");
                            if (user) {
                                std::cout << *user;
                            } else {
                                std::cout << "该用户不存在" << std::endl;
                            }
                            break;
                        }
                        case 2: {
                            std::cout << "请输入想查询用户的姓名：";
                            std::string name;
                            std::cin >> name;
                            auto user = list.fetchNode(name, "name");
                            if (user) {
                                std::cout << *user;
                            } else {
                                std::cout << "该用户不存在" << std::endl;
                            }
                            flag = false;
                            break;
                        }
                        default: {
                            std::cout << "输入有误，请重新输入\n";
                            break;
                        }
                    }
                    if (typeNum_)
                        menu.displayFetchMenu();
                }
                break;
            }
            // 展示学生信息
            case 3: {
                std::cout << std::setw(20) << std::setfill('-') << "-"
                          << std::endl;
                list.display();
                break;
            }
            // 排序学生信息
            case 4: {
                std::cout << std::setw(20) << std::setfill('-') << "-"
                          << std::endl;
                if (!list.getSize()) {
                    std::cout << "当前链表为空" << std::endl;
                    break;
                }
                list.sortNode();
                file.change(list);
                break;
            }
            // 显示机器使用情况
            case 5: {
                std::cout << std::setw(20) << std::setfill('-') << "-"
                          << std::endl;
                mp.displayMap();
                break;
            }
            default:
                std::cout << "输入有误，请重新输入\n";
                break;
        }
        if (userChoice)
            menu.displayMainMenu();
    }
    file.change(list);
    system("pause");
    return 0;
}
