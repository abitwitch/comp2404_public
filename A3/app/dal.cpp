//Author: Josh Chisholm (100770668)
//file dal.cpp
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "dal.h"

#include "sharedFunctions.h"
#include "database.h"

using namespace std;

//constructor
Dal::Dal():
  db("beatles.db")
  {
    //body of the constructor
  }

//destructor
Dal::~Dal(){

}

//copy constructor
Dal::Dal( const Dal & aDal):db("beatles.db") { //todo add a getter and get dbfilename from aDal.db

}

//assignment operator
Dal & Dal::operator=(const Dal & aDal) {
    if(&aDal != this) {
      //db=aDal.db; TODO fix this
		}
		return *this;
}


string Dal::addObj(vector<string> args){
  //Replace ' with '' for sql
  for (int i = 0; i < args.size(); i++) {
    string newArg;
    for (auto& iter : args[i]){
      if(iter=='\''){
        newArg.push_back('\'');
      }
      newArg.push_back(iter);
    }
    args[i]=newArg;
  }

  if (args.size()<2){
    return "Error: Wrong number of arguments for add. Please check command.\n";
  } else if (args[1]=="-r"){
    //Recordings
    if (args.size()!=5+2){
      return "Error: Wrong number of arguments for add -r. Please check command.\n";
    }
    return db.addRecording(args[2],args[3],args[4],args[5],args[6]);
  } else if (args[1]=="-s"){
    //Songs
    if (args.size()!=3+2){
      return "Error: Wrong number of arguments for add -s. Please check command.\n";
    }
    return db.addSong(args[2],args[3],args[4]);
  } else if (args[1]=="-t"){
    //Tracks
    if (args.size()!=4+2){
      return "Error: Wrong number of arguments for add -t. Please check command.\n";
    }
    return db.addTrack(args[2],args[3],args[4],args[5]);
  } else if (args[1]=="-u"){
    //Users
    if (args.size()!=2+2){
      return "Error: Wrong number of arguments for add -u. Please check command.\n";
    }
    return db.addUser(args[2],args[3]);
  } else if (args[1]=="-p"){
    //Playlists
    if (args.size()!=2+2){
      return "Error: Wrong number of arguments for add -p. Please check command.\n";
    }
    return db.addPlaylist(args[2],args[3]);
  } else if (args[1]=="-l"){
    //Track to playlist
    if (args.size()!=3+2){
      return "Error: Wrong number of arguments for add -l. Please check command.\n";
    }
    return db.addTrackToPlaylist(args[2],args[3],args[4]);
  } else{
    //Unknown flag
    return "Error: Unknown flag. Please check command.\n";
  }
}
string Dal::deleteObj(string id, string type){
  //Overloaded method to delete an object after it's been parsed by the other method of the SAME name
  if(type=="songs"){
    //Delete all tracks with that song_id
    db.deleteTracksBySongID(id);
    //Delete song
    return db.deleteSong(id);
  } else if(type=="recordings"){
    //Delete all tracks with that recording_id
    db.deleteTracksByRecordingID(id);
    //Delete recording
    return db.deleteRecording(id);
  } else if(type=="tracks"){
    //Remove track from all playlists
    db.deletePlaylistTracksByTrackID(id);
    //Delete track
    return db.deleteTrack(id);
  } else if(type=="users"){
    //All playlists with that user_id
    db.deletePlaylistsByUserID(id);
    //Delete user
    return db.deleteUser(id);
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
    return db.deletePlaylist(user_id,playlist_name);

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
      return db.removeTrackFromPlaylist(user_id,playlist_name,track_id);
    }

  } else {
    return "Error: Wrong number of arguments for delete. Please check command.\n";
  }
}

string Dal::showObj(vector<string> args){
  if (args.size()<2){
    return "Error: Wrong number of arguments for show. Please check command.\n";//+toStr()+"";
  } else if (args[1]=="songs" && args.size()==0+2){
    //Songs (exactly 2 arguments)
    return db.listAllSongs();
  } else if (args[1]=="users"){
    //Users
    if (args.size()!=0+2){
      return "Error: Wrong number of arguments for show users. Please check command.\n";
    }
    return db.listAllUsers();
  } else if (args[1]=="playlists"){
    //Playlists
    if (args.size()!=2+2){
      return "Error: Wrong number of arguments for show playlists. Please check command.\n";
    }
    if (args[2]!="-u"){
      return "Error: Expecting -u tag for show playlists. Please check command.\n";
    }
    return db.listPlaylistsByUser(args[3]);
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
    return db.listSongsByPlaylist(user_id,playlist_name);
  } else if (args[1]=="recordings"){
    //Recordings
    if (args.size()!=0+2){
      return "Error: Wrong number of arguments for show recordings. Please check command.\n";
    }
    return db.listAllRecordings();
  } else if (args[1]=="tracks"){
    //Tracks
    if (args.size()!=0+2){
      return "Error: Wrong number of arguments for show tracks. Please check command.\n";
    }
    return db.listAllTracks();
  } else {
    //Unknown flag
    return "Error: Unknown flag. Please check command.\n";
  }

}





string Dal::toStr() const {
  //return "Data Access Layer: "+ db.getDbfilename() + "\n";
  return "Data Access Layer\n";
}

ostream & operator<<(ostream & out, const Dal & p) {
   out << p.toStr();
   return out;
}
