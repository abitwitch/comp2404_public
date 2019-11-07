//Author: Josh Chisholm (100770668)
//file user.cpp
#include <iostream>
#include <string>
#include <fstream>

#include "user.h"

using namespace std;

//constructor
User::User(string a_user_id, string a_name):
  user_id(a_user_id),
  name(a_name)
  {
    //body of the constructor
  }
//destructor
User::~User(){
  //todo
  for (int i = 0; i < playlists.size(); i++) {
    delete playlists[i];
  }
}

//copy constructor
User::User( const User & aUser) {
		user_id = aUser.user_id;
    name = aUser.name;
}

//assignment operator
User & User::operator=(const User & aUser) {
    if(&aUser != this) {
      user_id = aUser.user_id;
      name = aUser.name;
		}
		return *this;
}

int User::findIndexOfPlaylist(string id){
  for (int i = 0; i < playlists.size(); i++) {
    if (playlists[i]->getId()==id){
      return i;
    }
  }
  return -1;
}

//getters
string User::getId(){
  return user_id;
}
string User::listPlaylists(){
  string toReturn="Playlist:\n";
  for (int i = 0; i < playlists.size(); i++) {
    toReturn.append("  -"+playlists[i]->toStr());
  }
  return toReturn;
}
vector<string> User::listTrackIDsInPlaylists(string a_playlist_id){
  int index=findIndexOfPlaylist(a_playlist_id);
  if(index==-1){
    return {};
  }
  return playlists[index]->getTrack_ids();
}

//setters
string User::addPlaylist(string a_user_id, string a_playlist_name){
  if(findIndexOfPlaylist(a_user_id+a_playlist_name)!=-1){
    return "Error: Playlist ID already exists for user. Please check command.\n";
  }
  playlists.push_back(new Playlist(a_user_id,a_playlist_name));
  return "Added playlist.\n";
}

string User::deletePlaylist(string id){
  int index=findIndexOfPlaylist(id);
  if(index==-1){
    return "Error: Playlist not found. Please check command.\n";
  }
  delete playlists[index];
  playlists.erase (playlists.begin()+index);
  return "Playlist delete.\n";
}

string User::addTrackToPlaylist(string a_playlist_id, string a_track_id){
  int index=findIndexOfPlaylist(a_playlist_id);
  if(index==-1){
    return "Error: Playlist not found. Please check command.\n";
  }
  playlists[index]->addTrack(a_track_id);
  return "Added track to playlist.\n";
}

string User::removeTrackFromPlaylist(string a_playlist_id, string a_track_id){
  int index=findIndexOfPlaylist(a_playlist_id);
  if(index==-1){
    return "Error: Playlist not found. Please check command.\n";
  }
  playlists[index]->removeTrack(a_track_id);
  return "Track deleted.\n";
}

void User::removeTrackFromAllPlaylists(string a_track_id){
  for (int i = 0; i < playlists.size(); i++) {
    playlists[i]->removeTrack(a_track_id);//we are calling this on all playlist even through the track might not exist in each
  }
}


string User::toStr() const {
  return "User: " + name + "\n";
}

ostream & operator<<(ostream & out, const User & p) {
   out << p.toStr();
   return out;
}
