#ifndef USERLIST_H
#define USERLIST_H
#include "info.h"
#include "list.h"

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

#endif  // USERLIST_H
