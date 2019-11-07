//Author: Josh Chisholm (100770668)
//file: playlist.h
#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Playlist {
  private:
    string user_id;
    string playlist_name;
    string playlist_id;
    vector<string> track_ids;
  public:
    Playlist(string a_user_id, string a_playlist_name);
    ~Playlist();
    Playlist( const Playlist & aPlaylist);
    Playlist & operator=(const Playlist & aPlaylist);
    string getId();
    string toStr() const;
    void addTrack(string a_track_id);
    void removeTrack(string a_track_id);
    string getUser_id();
    vector<string> getTrack_ids();
};

ostream & operator<<(ostream & out, const Playlist & p);

#endif
