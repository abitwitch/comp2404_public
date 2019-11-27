//Author: Josh Chisholm (100770668)
//file: dal.h
#ifndef DAL_H
#define DAL_H

#include <iostream>
#include <string>
#include <vector>

#include "database.h"

using namespace std;


class Dal {
  private:
    Database db;
  public:
    Dal();
    ~Dal();
    Dal( const Dal & aDal);
    Dal & operator=(const Dal & aDal);

    string addObj(vector<string> args);
    string deleteObj(vector<string> args);
    string deleteObj(string id, string type);
    string showObj(vector<string> args);
    int findIndexOfObj(string id, string type);
    string toStr() const;
};

ostream & operator<<(ostream & out, const Dal & p);

#endif
