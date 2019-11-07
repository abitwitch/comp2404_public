//Author: Josh Chisholm (100770668)
//file: dal.h
#ifndef DAL_H
#define DAL_H

#include <iostream>
#include <string>
#include <vector>

#include "song.h"
#include "recording.h"
#include "track.h"
#include "user.h"
#include "playlist.h"

using namespace std;


class Dal {
  private:
    vector<Song *> songs;
    vector<Recording *> recordings;
    vector<Track *> tracks;
    vector<User *> users;
  public:
    Dal();
    ~Dal();
    Dal( const Dal & aDal);
    Dal & operator=(const Dal & aUser);
    string addObj(vector<string> args);
    string deleteObj(vector<string> args);
    string deleteObj(string id, string type);
    string showObj(vector<string> args);
    int findIndexOfObj(string id, string type);
    string toStr() const;
};

ostream & operator<<(ostream & out, const Dal & p);

#endif
