//Author: Josh Chisholm (100770668)
//file: user.h
#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

#include "playlist.h"

using namespace std;

class User {
  private:
    string user_id;
    string name;
    vector<Playlist *> playlists;
  public:
    User(string a_user_id, string a_name);
    ~User();
    User( const User & aUser);
    User & operator=(const User & aUser);
    string getId();
    string toStr() const;
    int findIndexOfPlaylist(string id);
    string addPlaylist(string a_user_id, string a_playlist_name);
    string listPlaylists();
    string addTrackToPlaylist(string a_playlist_id, string a_track_id);
    string removeTrackFromPlaylist(string a_playlist_id, string a_track_id);
    void removeTrackFromAllPlaylists(string a_track_id);
    vector<string> listTrackIDsInPlaylists(string a_playlist_id);
    string deletePlaylist(string id);
};

ostream & operator<<(ostream & out, const User & p);


#endif
