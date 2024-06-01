#ifndef FILE_H
#define FILE_H

#include <fstream>
#include "userList.h"

class File {
   public:
    File(const std::string, const std::string);

    void init(UserList&);

    void add(Info&);

    void change(UserList&);

   private:
    std::string path;
    std::string fileType;
};
#endif  // FILE_H
