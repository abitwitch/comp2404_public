//Author: Josh Chisholm (100770668)
//file: fileobj.h
#ifndef FILEOBJ_H
#define FILEOBJ_H

#include <iostream>
#include <string>
using namespace std;

class FileObj {
  private:
    string path;
    string contents;
    bool accessible;
  public:
    FileObj(string path);
    ~FileObj();
    string read();
};
#endif
