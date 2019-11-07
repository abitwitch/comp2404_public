//Author: Josh Chisholm (100770668)
//file dal.cpp
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "dal.h"

#include "song.h"
#include "recording.h"
#include "track.h"
#include "user.h"
#include "playlist.h"

using namespace std;

//constructor
Dal::Dal(){
    //body of the constructor

  }
//destructor
Dal::~Dal(){
  // //songs
  // for (auto * p : songs) {
  //   delete p;
  // }
  // songs.clear();
  // //recordings
  // for (auto p : recordings) {
  //   delete p;
  // }
  // recordings.clear();
  // //tracks
  // for (auto p : tracks) {
  //   delete p;
  // }
  // tracks.clear();
  // //users
  // for (auto p : users) {
  //   delete p;
  // }
  // users.clear();
}

//copy constructor
Dal::Dal( const Dal & aDal) {
  songs=aDal.songs;
  recordings=aDal.recordings;
  tracks=aDal.tracks;
  users=aDal.users;
}

//assignment operator
Dal & Dal::operator=(const Dal & aDal) {
    if(&aDal != this) {
      songs=aDal.songs;
      recordings=aDal.recordings;
      tracks=aDal.tracks;
      users=aDal.users;
		}
		return *this;
}

int Dal::findIndexOfObj(string id, string type){
  if(type=="songs"){
    for (int i = 0; i < songs.size(); i++) {
      if (songs[i]->getId()==id){
        return i;
      }
    }
    return -1;
  } else if(type=="recordings"){
    for (int i = 0; i < recordings.size(); i++) {
      if (recordings[i]->getId()==id){
        return i;
      }
    }
    return -1;
  } else if(type=="tracks"){
    for (int i = 0; i < tracks.size(); i++) {
      if (tracks[i]->getId()==id){
        return i;
      }
    }
    return -1;
  } else if(type=="users"){
    for (int i = 0; i < users.size(); i++) {
      if (users[i]->getId()==id){
        return i;
      }
    }
    return -1;
  } else {
    return -1;
  }
}

string Dal::addObj(vector<string> args){
  if (args.size()<2){
    return "Error: Wrong number of arguments for add. Please check command.\n";
  } else if (args[1]=="-r"){
    //Recordings
    if (args.size()!=5+2){
      return "Error: Wrong number of arguments for add -r. Please check command.\n";
    }
    if (findIndexOfObj(args[2],"recordings")!=-1){
      return "Error: Recording ID already exists. Please check command.\n";
    }
    recordings.push_back(new Recording(args[2],args[3],args[4],args[5],args[6]));
    return "Added recording.\n";
  } else if (args[1]=="-s"){
    //Songs
    if (args.size()!=3+2){
      return "Error: Wrong number of arguments for add -s. Please check command.\n";
    }
    if (findIndexOfObj(args[2],"songs")!=-1){
      return "Error: Song ID already exists. Please check command.\n";
    }
    songs.push_back(new Song(args[2],args[3],args[4]));
    return "Added song.\n";
  } else if (args[1]=="-t"){
    //Tracks
    if (args.size()!=4+2){
      return "Error: Wrong number of arguments for add -t. Please check command.\n";
    }
    if (findIndexOfObj(args[2],"tracks")!=-1){
      return "Error: Track ID already exists. Please check command.\n";
    }
    tracks.push_back(new Track(args[2],args[3],args[4],args[5]));
    return "Added track.\n";
  } else if (args[1]=="-u"){
    //Users
    if (args.size()!=2+2){
      return "Error: Wrong number of arguments for add -u. Please check command.\n";
    }
    if (findIndexOfObj(args[2],"users")!=-1){
      return "Error: User ID already exists. Please check command.\n";
    }
    users.push_back(new User(args[2],args[3]));
    return "Added user.\n";
  } else if (args[1]=="-p"){
    //Playlists
    if (args.size()!=2+2){
      return "Error: Wrong number of arguments for add -p. Please check command.\n";
    }
    int index=findIndexOfObj(args[2],"users");
    if (index==-1){
      return "Error: Cannot find user by id. Please check command.\n";
    }
    return users[index]->addPlaylist(args[2],args[3]);
  } else if (args[1]=="-l"){
    //Track to playlist
    if (args.size()!=3+2){
      return "Error: Wrong number of arguments for add -l. Please check command.\n";
    }
    int index=findIndexOfObj(args[2],"users");
    if (index==-1){
      return "Error: Cannot find user by id. Please check command.\n";
    }
    return users[index]->addTrackToPlaylist(args[2]+args[3],args[4]);
  } else{
    //Unknown flag
    return "Error: Unknown flag. Please check command.\n";
  }
}
string Dal::deleteObj(string id, string type){
  //Overloaded method to delete an object after it's been parsed by the other method of the SAME name
  int index=findIndexOfObj(id,type);
  if (index==-1){
    return "Error: Unable to find id. Please check command.\n";
  }
  if(type=="songs"){
    //Delete all tracks with that song_id
    vector<string> toDel;
    for (int i = 0; i < tracks.size(); i++) {
      if (id==tracks[i]->getSong_id()){
        toDel.push_back(tracks[i]->getId());
      }
    }
    for (int i = 0; i < toDel.size(); i++) {
      deleteObj(toDel[i],"tracks");
    }
    //Delete song
    delete songs[index];
    songs.erase (songs.begin()+index);
    return "Song deleted.\n";
  } else if(type=="recordings"){
    //Delete all tracks with that recording_id
    vector<string> toDel;
    for (int i = 0; i < tracks.size(); i++) {
      if (id==tracks[i]->getRecording_id()){
        toDel.push_back(tracks[i]->getId());
      }
    }
    for (int i = 0; i < toDel.size(); i++) {
      deleteObj(toDel[i],"tracks");
    }
    //Delete recording
    delete recordings[index];
    recordings.erase (recordings.begin()+index);
    return "Recording deleted.\n";
  } else if(type=="tracks"){
    //Remove track from all playlists
    for (int i = 0; i < users.size(); i++) {
      users[i]->removeTrackFromAllPlaylists(id);
    }
    //Delete track
    delete tracks[index];
    tracks.erase (tracks.begin()+index);
    return "Track deleted.\n";
  } else if(type=="users"){
    //All playlists with that user_id will be deleted on destruction
    //Delete user
    delete users[index];
    users.erase (users.begin()+index);
    return "User deleted.\n";
  } else {
    return "Error: Unknown flag. Please check command.\n";
  }
}

string Dal::deleteObj(vector<string> args){
  //Overloaded method to parse data before it is deleted by the other method of the SAME name
  string type;
  if (args.size()==3){
    //simple delte cases
    if      (args[1]=="-s") { type="songs"; }
    else if (args[1]=="-u") { type="users"; }
    else if (args[1]=="-t") { type="tracks"; }
    else if (args[1]=="-r") { type="recordings"; }
    else { return "Error: Unknown flag. Please check command.\n"; }

    return deleteObj(args[2],type);

  } else if(args.size()==5) {
    //simple delete for playlists
    type="playlists";
    string user_id="";
    if (args[1]=="-u"){
      user_id=args[2];
    }
    if (args[3]=="-u"){
      user_id=args[4];
    }
    string playlist_name="";
    if (args[1]=="-p"){
      playlist_name=args[2];
    }
    if (args[3]=="-p"){
      playlist_name=args[4];
    }
    if (playlist_name==""||user_id==""){
      return "Error: Expecting -u and -p tags for show playlists. Please check command.\n";
    }
    int index=findIndexOfObj(user_id,"users");
    if (index==-1){
      return "Error: Cannot find user by id. Please check command.\n";
    }
    return users[index]->deletePlaylist(user_id+playlist_name);

  } else if(args.size()==7 || args.size()==8) {
    string track_id="";
    string playlist_name="";
    string user_id="";
    bool global=false;
    for (int i = 0; i < args.size()-1; i++) {
      if (args[i]=="-t"){ track_id=args[i+1]; }
      if (args[i]=="-s"){ track_id=args[i+1]; } //DEPRECATED but still supported
      if (args[i]=="-p"){ playlist_name=args[i+1]; }
      if (args[i]=="-u"){ user_id=args[i+1]; }
      if (args[i]=="-Global"){ global=true; }
    }
    if(global){
      return deleteObj(track_id,"tracks");
    } else {
      if(args.size()==8){
        return "Error: Wrong number of arguments or unknown arguments for delete. Please check command.\n";
      }
      int index=findIndexOfObj(user_id,"users");
      if (index==-1){
        return "Error: Cannot find user by id. Please check command.\n";
      }
      return users[index]->removeTrackFromPlaylist(user_id+playlist_name,track_id);
    }

  } else {
    return "Error: Wrong number of arguments for delete. Please check command.\n";
  }

}

string Dal::showObj(vector<string> args){
  if (args.size()<2){
    return "Error: Wrong number of arguments for show. Please check command.\n"+toStr()+"";
  } else if (args[1]=="songs" && args.size()==0+2){
    //Songs (exactly 2 arguments)
    string toReturn="Songs:\n";
    for (int i = 0; i < songs.size(); i++) {
      toReturn.append("  -"+songs[i]->toStr());
    }
    return toReturn;
  } else if (args[1]=="users"){
    //Users
    if (args.size()!=0+2){
      return "Error: Wrong number of arguments for show users. Please check command.\n";
    }
    string toReturn="Users:\n";
    for (int i = 0; i < users.size(); i++) {
      toReturn.append("  -"+users[i]->toStr());
    }
    return toReturn;
  } else if (args[1]=="playlists"){
    //Playlists
    if (args.size()!=2+2){
      return "Error: Wrong number of arguments for show playlists. Please check command.\n";
    }
    if (args[2]!="-u"){
      return "Error: Expecting -u tag for show playlists. Please check command.\n";
    }
    int index=findIndexOfObj(args[3],"users");
    if (index==-1){
      return "Error: Cannot find user by id. Please check command.\n";
    }
    return users[index]->listPlaylists();
  } else if (args[1]=="songs"){
    //Songs (2+ arguments)
    if (args.size()!=4+2){
      return "Error: Wrong number of arguments for show songs. Please check command.\n";
    }
    string user_id="";
    if (args[2]=="-u"){
      user_id=args[3];
    }
    if (args[4]=="-u"){
      user_id=args[5];
    }
    string playlist_name="";
    if (args[2]=="-p"){
      playlist_name=args[3];
    }
    if (args[4]=="-p"){
      playlist_name=args[5];
    }
    if (playlist_name==""||user_id==""){
      return "Error: Expecting -u and -p tags for show playlists. Please check command.\n";
    }
    string toReturn="Songs:\n";
    int index=findIndexOfObj(user_id,"users");
    if (index==-1){
      return "Error: Cannot find user by id. Please check command.\n";
    }
    vector<string> track_ids=users[index]->listTrackIDsInPlaylists(user_id+playlist_name);
    for (int i = 0; i < track_ids.size(); i++) {
      index=findIndexOfObj(track_ids[i],"tracks");
      string song_id=tracks[index]->getSong_id();
      index=findIndexOfObj(song_id,"songs");
      toReturn.append("  -"+songs[index]->toStr());
    }
    return toReturn;
  } else if (args[1]=="recordings"){
    //Recordings
    if (args.size()!=0+2){
      return "Error: Wrong number of arguments for show recordings. Please check command.\n";
    }
    string toReturn="Recordings:\n";
    for (int i = 0; i < recordings.size(); i++) {
      toReturn.append("  -"+recordings[i]->toStr());
    }
    return toReturn;
  } else if (args[1]=="tracks"){
    //Tracks
    if (args.size()!=0+2){
      return "Error: Wrong number of arguments for show tracks. Please check command.\n";
    }
    string toReturn="Tracks:\n";
    int song_index;
    int recording_index;
    for (int i = 0; i < tracks.size(); i++) {
      string track_number=tracks[i]->getTrack_number();
      song_index=findIndexOfObj(tracks[i]->getSong_id(),"songs");
      if (song_index==-1){
        toReturn.append("  -Error: track is linked to song that does not exist.\n");
        continue;
      }
      string song_title=songs[song_index]->getTitle();
      recording_index=findIndexOfObj(tracks[i]->getRecording_id(),"recordings");
      if (recording_index==-1){
        toReturn.append("  -Error: track is linked to recording that does not exist.\n");
        continue;
      }
      string album_title=recordings[recording_index]->getTitle();
      toReturn.append("  -Track: "+track_number);
      toReturn.append(" ("+song_title+" from "+album_title+")");
      toReturn.append("\n");
    }
    return toReturn;
  } else {
    //Unknown flag
    return "Error: Unknown flag. Please check command.\n";
  }

}





string Dal::toStr() const {
  return "Data Access Layer: "
  + to_string(songs.size()) + " Song(s), "
  + to_string(recordings.size()) + " Recording(s), "
  + to_string(tracks.size()) + " Track(s), "
  + to_string(users.size()) + " User(s)\n";
}

ostream & operator<<(ostream & out, const Dal & p) {
   out << p.toStr();
   return out;
}
