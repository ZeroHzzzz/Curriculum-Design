//
// 用户数据链表类的实现文件
// Created by 15928 on 2022/4/28.
//

#include "../include/userList.h"
#include <regex>
#include <utility>
#include "../include/machine.h"
#include "../include/student.h"
// 空对象

ListNode<Info>* UserList::fetchNode(const std::string& context,
                                    const std::string& type) {
    // 查询功能,type控制查询的方法，支持用姓名、手机号、类型查询
    ListNode<Info>* ptr = head;

    if (type == "num") {
        while (ptr) {
            if (ptr->getData().getNum() == context) {
                return ptr;
            }
            ptr = ptr->getNext();
        }
    } else if (type == "name") {
        // 处理重名情况
        int num = 0;
        ListNode<Info>* ptr_[getSize()];
        while (ptr) {
            if (ptr->getData().getName() == context) {
                ptr_[num] = ptr;
                if (num == 1) {
                    std::cout
                        << "查询到多个用户，请输入对应用户前的编号进行选择"
                        << std::endl;
                    std::cout << "NO.1" << std::endl << *ptr_[0];
                    std::cout << "NO.2" << std::endl << *ptr;
                } else if (num) {
                    std::cout << "NO." << (num + 1) << std::endl << *ptr;
                }
                num++;
            }
            ptr = ptr->getNext();
        }
        if (num > 1) {
            int val;
            std::cin >> val;
            if (val <= num) {
                return ptr_[val - 1];
            } else {
                return ptr_[num - 1];
            }
        } else if (num == 1) {
            return ptr_[0];
        }
    } else if (type == "className") {
        while (ptr) {
            if (ptr->getData().getClassName() == context) {
                std::cout << *ptr;
            }
            ptr = ptr->getNext();
        }
    }
    return nullptr;
}

void UserList::delNode(const std::string& context, const std::string& type) {
    // 删除功能，type控制查询的方法，支持用姓名与手机号查询
    ListNode<Info>* ptr = fetchNode(context, type);
    if (!ptr) {
        std::cout << "不存在该用户" << std::endl;
        return;
    }
    ListNode<Info>* ptr_ = ptr->getPrior();
    if (ptr_ && ptr->getNext()) {
        ptr_->setNext(ptr->getNext());
        ptr->getNext()->setPrior(ptr_);
    } else if (ptr_) {
        // 删尾节点
        ptr_->setNext(nullptr);
        tail = ptr_;
    } else if (ptr->getNext()) {
        // 删头节点
        ptr->getNext()->setPrior(nullptr);
        head = ptr->getNext();
    } else {
        // 删链表唯一节点
        tail = nullptr;
        head = nullptr;
    }
    --size;
    delete ptr;
    ptr = nullptr;
    std::cout << "----------------------------------------" << std::endl;
    display();
}

void UserList::changeNode_info(std::string context) {
    auto user = fetchNode(context, "num");
    if (user) {
        std::string temp;
        std::cout << "请输入上机结束时间:";
        while (std::cin >> temp) {
            std::regex timePattern(R"(^([01][0-9]|2[0-3]):[0-5][0-9]$)");
            if (std::regex_match(temp, timePattern)) {
                if (parseTimeToMinutes(user->getData().getBeginTime()) >
                    parseTimeToMinutes(temp)) {
                    std::cout << "结束时间不能早于开始时间！请重新输入：";
                } else {
                    user->getData().setEndTime(temp);
                    break;
                }
            } else {
                std::cout << "时间格式不正确，应为 HH:MM :";
            }
        }
        user->getData().setTotalTime();
        user->getData().calculateCost(user->getData().getTotalTime());
        mp.changeMachineStatus(user->getData().getMachineNum(), "FREE");
        display();
    } else {
        // 查询数据出错的情况
        std::cout << "未能找到该用户的上机信息！" << std::endl;
    }
}

void UserList::changeNode(std::string context, const std::string& type) {
    // 修改功能，type控制查询的方法
    auto user =
        type == "name" ? fetchNode(context, "name") : fetchNode(context, "num");
    if (user) {
        std::cout << "请输入需要改变的数据名编号" << std::endl
                  << "1: 学号" << std::endl
                  << "2: 姓名" << std::endl
                  << "3: 班级" << std::endl
                  << "4: 机器编号" << std::endl
                  << "5: 上机开始时间" << std::endl
                  << "6: 上机结束时间" << std::endl
                  << "0: 退出" << std::endl
                  << "<";
        int typeNum;
        bool flag = true;

        while (flag && std::cin >> typeNum && typeNum) {
            switch (typeNum) {
                case 1: {
                    std::string temp;
                    std::cout << "请输入新的学号:";
                    std::cin >> temp;
                    if (type == "num") {
                        user->getData().setNum(temp);
                        context = temp;
                    } else if (type == "name") {
                        user->getData().setNum(temp);
                    }
                    display();
                    flag = false;
                    break;
                }
                case 2: {
                    std::string temp;
                    std::cout << "请输入新的姓名:";
                    std::cin >> temp;
                    if (type == "name") {
                        user->getData().setName(temp);
                        context = temp;
                    } else if (type == "num") {
                        user->getData().setName(temp);
                    }
                    display();
                    flag = false;
                    break;
                }
                case 3: {
                    std::string temp;
                    std::cout << "请输入新的班级:";
                    std::cin >> temp;
                    if (type == "name") {
                        user->getData().setClassName(temp);
                        context = temp;
                    } else if (type == "num") {
                        user->getData().setClassName(temp);
                    }
                    display();
                    flag = false;
                    break;
                }
                case 4: {
                    std::string temp;
                    std::cout << "请输入新的机器编号:";
                    std::cin >> temp;
                    Info tmp = user->getData();
                    if (type == "name") {
                        user->getData().setMachineNum(temp);
                        context = temp;
                    } else if (type == "num") {
                        user->getData().setMachineNum(temp);
                    }
                    mp.updateMachineStatus(tmp, user->getData());
                    display();
                    flag = false;
                    break;
                }
                case 5: {
                    std::string temp;
                    std::cout << "请输入上机开始时间:";
                    while (std::cin >> temp) {
                        std::regex timePattern(R"(^\d{2}:\d{2}$)");
                        if (std::regex_match(temp, timePattern)) {
                            if (type == "name") {
                                user->getData().setBeginTime(temp);
                                context = temp;
                            } else if (type == "num") {
                                user->getData().setBeginTime(temp);
                            }
                            break;
                        } else {
                            std::cout << "时间格式不正确，应为 HH:MM :";
                        }
                    }
                    user->getData().setTotalTime();
                    user->getData().calculateCost(
                        user->getData().getTotalTime());
                    display();
                    flag = false;
                    break;
                }
                case 6: {
                    std::string temp;
                    std::cout << "请输入上机结束时间:";
                    while (std::cin >> temp) {
                        std::regex timePattern(R"(^\d{2}:\d{2}$)");
                        if (std::regex_match(temp, timePattern)) {
                            if (type == "name") {
                                user->getData().setEndTime(temp);
                                context = temp;
                            } else if (type == "num") {
                                user->getData().setEndTime(temp);
                            }
                            break;
                        } else {
                            std::cout << "时间格式不正确，应为 HH:MM :";
                        }
                    }
                    user->getData().setTotalTime();
                    user->getData().calculateCost(
                        user->getData().getTotalTime());
                    display();
                    flag = false;
                    break;
                }
                default: {
                    std::cout << "输入有误，请重新输入\n>";
                    break;
                }
            }
        }
    } else {
        // 查询数据出错的情况
        std::cout << "未能找到该用户" << std::endl;
    }
}

void UserList::sortNode() {
    // 排序功能
    std::cout << "请输入排序关键词的编号:" << std::endl
              << "1: 学号" << std::endl
              << "2: 姓名" << std::endl
              << "3: 班级" << std::endl
              << "4: 上机时长" << std::endl
              << "0: 返回上级菜单" << std::endl
              << "<";
    int type;
    std::cin >> type;
    switch (type) {
        case 0:
            return;
        case 1: {
            sort([](const ListNode<Info>& left,
                    const ListNode<Info>& right) -> bool {
                return left.getData().getNum() < right.getData().getNum();
            });
            display();
            break;
        }
        case 2: {
            sort([](const ListNode<Info>& left,
                    const ListNode<Info>& right) -> bool {
                return left.getData().getName() < right.getData().getName();
            });
            display();
            break;
        }
        case 3: {
            sort([](const ListNode<Info>& left,
                    const ListNode<Info>& right) -> bool {
                return left.getData().getClassName() <
                       right.getData().getClassName();
            });
            display();
            break;
        }
        case 4: {
            sort([](const ListNode<Info>& left,
                    const ListNode<Info>& right) -> bool {
                return left.getData().getTotalTime() <
                       right.getData().getTotalTime();
            });
            display();
            break;
        }
        default: {
            std::cout << "输入有误，已自动返回上级菜单" << std::endl;
            break;
        }
    }
}

void UserList::sort(bool (*cmp)(const ListNode<Info>&, const ListNode<Info>&)) {
    // 排序实现，现阶段利用插入排序
    ListNode<Info>* ptr = head;
    ListNode<Info>* ptr_ = nullptr;
    ListNode<Info>* ptr_tmp = nullptr;
    for (int i = 0; i < getSize() - 1; i++) {
        ptr_ = ptr->getNext();
        ptr_tmp = ptr;
        for (int j = i + 1; j < getSize(); j++) {
            if (cmp(*ptr_, *ptr_tmp)) {
                ptr_tmp = ptr_;
            }
            ptr_ = ptr_->getNext();
        }
        if (ptr != ptr_tmp) {
            swap(ptr, ptr_tmp);
            ptr = ptr_tmp;
        }
        ptr = ptr->getNext();
    }
}

void UserList::swap(ListNode<Info>* left, ListNode<Info>* right) {
    // 交换两个节点的前后关联
    head = left == head ? right : head;
    tail = right == tail ? left : tail;

    if (left->getNext() == right) {
        // 交换的节点相邻
        ListNode<Info>* prior = left->getPrior();
        ListNode<Info>* next = right->getNext();

        left->setNext(next);
        if (next) {
            next->setPrior(left);
        }
        left->setPrior(right);

        right->setPrior(prior);
        if (prior) {
            prior->setNext(right);
        }
        right->setNext(left);
    } else {
        // 交换的节点不相邻
        if (left->getPrior()) {
            left->getPrior()->setNext(right);
        }
        ListNode<Info>* prior = right->getPrior();
        prior->setNext(left);
        right->setPrior(left->getPrior());
        left->setPrior(prior);
        prior = nullptr;

        left->getNext()->setPrior(right);
        ListNode<Info>* next = right->getNext();
        if (next) {
            next->setPrior(left);
        }
        right->setNext(left->getNext());
        left->setNext(next);
        next = nullptr;
    }
}
