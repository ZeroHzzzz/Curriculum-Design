#include "../include/Menu.h"
#include <iomanip>
#include <iostream>

void Menu::displayMainMenu() {
    std::cout << std::endl;
    std::cout << std::setw(20) << std::setfill('-') << "-" << std::endl;
    std::cout << "请输入你的选择: " << std::endl;
    std::cout << "1. 选手管理" << std::endl;
    std::cout << "2. 评委打分" << std::endl;
    std::cout << "3. 排序" << std::endl;
    std::cout << "4. 打印所有选手信息" << std::endl;
    std::cout << "5. 文件操作" << std::endl;
    std::cout << "0. 退出" << std::endl;
    std::cout << ">";
}

void Menu::displayManageMenu() {
    std::cout << std::endl;
    std::cout << std::setw(20) << std::setfill('-') << "-" << std::endl;
    std::cout << "请输入你的选择: " << std::endl;
    std::cout << "1. 添加选手" << std::endl;
    std::cout << "2. 修改选手信息" << std::endl;
    std::cout << "3. 删除选手" << std::endl;
    std::cout << "0. 返回主菜单" << std::endl;
    std::cout << ">";
}

void Menu::displaySortMenu() {
    std::cout << std::endl;
    std::cout << std::setw(20) << std::setfill('-') << "-" << std::endl;
    std::cout << "请输入你的选择: " << std::endl;
    std::cout << "1. 按照总成绩和平均分排序" << std::endl;
    std::cout << "2. 按某一评委评分排序" << std::endl;
    std::cout << "0. 返回主菜单" << std::endl;
    std::cout << ">";
}

void Menu::displayFileMenu() {
    std::cout << std::endl;
    std::cout << std::setw(20) << std::setfill('-') << "-" << std::endl;
    std::cout << "请输入你的选择: " << std::endl;
    std::cout << "1. 保存到文件" << std::endl;
    std::cout << "2. 从文件中加载" << std::endl;
    std::cout << "0. 返回主菜单" << std::endl;
    std::cout << ">";
}

void Menu::start() {
    int choice = 0;
    std::string filename;
    displayMainMenu();
    while (std::cin >> choice) {
        switch (choice) {
            case 0: {
                std::cout << "还没有保存，确定要退出吗(y/n):";
                char type;
                while (std::cin >> type) {
                    if (type == 'y')
                        return;
                    else
                        break;
                }
                break;
            }
            case 1: {
                displayManageMenu();
                int subChoice = 0;
                while (std::cin >> subChoice && subChoice) {
                    switch (subChoice) {
                        case 1: {
                            manager.addContestant();
                            break;
                        }
                        case 2: {
                            manager.displayAllContestants();
                            manager.modifyContestant();
                            break;
                        }
                        case 3: {
                            manager.displayAllContestants();
                            manager.deleteContestant();
                            break;
                        }
                        default: {
                            std::cout << "非法输入，请重新输入：" << std::endl
                                      << ">";
                            break;
                        }
                    }
                    if (subChoice)
                        displayManageMenu();
                }
                break;
            }
            case 2: {
                manager.displayAllContestants();
                manager.judgeContestant();
                break;
            }
            case 3: {
                manager.displayAllContestants();
                displaySortMenu();
                int subChoice = 0;
                while (std::cin >> subChoice && subChoice) {
                    switch (subChoice) {
                        case 1:
                            manager.sortContestants();
                            manager.displayAllContestants();
                            break;
                        case 2:
                            manager.sortByJudgeScore();
                            manager.displayAllContestants();
                            break;
                        default:
                            std::cout << "非法输入，请重新输入：" << std::endl
                                      << ">";
                    }
                    if (subChoice)
                        displaySortMenu();
                }
                break;
            }
            case 4: {
                manager.displayAllContestants();
                break;
            }
            case 5: {
                displayFileMenu();
                int subChoice = 0;
                while (std::cin >> subChoice && subChoice) {
                    switch (subChoice) {
                        case 1: {
                            std::cout << "输入文件名：" << std::endl << ">";
                            std::cin >> filename;
                            manager.saveToFile(filename);
                            break;
                        }
                        case 2: {
                            std::cout << "输入文件名：" << std::endl << ">";
                            std::cin >> filename;
                            manager.loadFromFile(filename);
                            break;
                        }
                        default:
                            std::cout << "非法输入，请重新输入：" << std::endl
                                      << ">";
                    }
                    if (subChoice)
                        displayFileMenu();
                }
                break;
            }
            default: {
                std::cout << "非法输入，请重新输入：" << std::endl << ">";
                break;
            }
        }
        displayMainMenu();
    }
}
