//
// 用户数据的链表类
// Created by 15928 on 2022/4/26.
//

#ifndef PROJECT_ABS_USERLIST_H
#define PROJECT_ABS_USERLIST_H
#include "list.h"
#include "student.h"

class UserList : public List<Info> {
   public:
    ListNode<Info>* fetchNode(const std::string&, const std::string&);

    void fetchNode();

    void delNode(const std::string&, const std::string&);

    void changeNode(std::string, const std::string&);

    void changeNode_info(std::string);

    void sortNode();

   private:
    void sort(bool (*cmp)(const ListNode<Info>&, const ListNode<Info>&));

    void swap(ListNode<Info>*, ListNode<Info>*);
};

#endif  // PROJECT_ABS_USERLIST_H
