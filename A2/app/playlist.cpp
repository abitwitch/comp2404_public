//Author: Josh Chisholm (100770668)
//file playlist.cpp
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "playlist.h"

using namespace std;

//constructor
Playlist::Playlist(string a_user_id, string a_playlist_name):
  user_id(a_user_id),
  playlist_name(a_playlist_name),
  playlist_id(a_user_id+a_playlist_name)
  {
    //body of constructor
  }

//destructor
Playlist::~Playlist(){
  //todo
}

//copy constructor
Playlist::Playlist( const Playlist & aPlaylist) {
		playlist_name = aPlaylist.playlist_name;
    user_id = aPlaylist.user_id;
    playlist_id = aPlaylist.playlist_id;
    track_ids = aPlaylist.track_ids;
}

//assignment operator
Playlist & Playlist::operator=(const Playlist & aPlaylist) {
    if(&aPlaylist != this) {
      playlist_name = aPlaylist.playlist_name;
      user_id = aPlaylist.user_id;
      playlist_id = aPlaylist.playlist_id;
      track_ids = aPlaylist.track_ids;
		}
		return *this;
}

//getters
string Playlist::getId(){
  return playlist_id;
}

string Playlist::getUser_id(){
  return user_id;
}

vector<string> Playlist::getTrack_ids(){
  return track_ids;
}

//setters
void Playlist::addTrack(string a_track_id){
  track_ids.push_back(a_track_id);
}

void Playlist::removeTrack(string a_track_id){
  for (int i=0; i<track_ids.size(); ++i){
    if(track_ids[i]==a_track_id){
      track_ids.erase(track_ids.begin()+i);
    }
  }
}



string Playlist::toStr() const {
  return "Playlist: " + playlist_name + "\n";
}

ostream & operator<<(ostream & out, const Playlist & p) {
   out << p.toStr();
   return out;
}
