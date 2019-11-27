//Author: Josh Chisholm (100770668)
//file log.cpp
#include <string>

#include "database.h"

#include "sqlite3.h"

using namespace std;

#include "sharedFunctions.h"

//constructor
Database::Database(string aDbfilename)
{
    //body of the constructor
    dbfilename=aDbfilename.c_str();
    zErrMsg=0;
    rc=-1;
    data="callback called";
    rc = sqlite3_open(dbfilename, &db);
    if(rc){
      cout << "ERROR: Could Not Open Database: "
           << sqlite3_errmsg(db);
      cout << "\nEXITING\n";
    }
}


//destructor
Database::~Database(){

}

//copy constructor
Database::Database(const Database & aDatabase) {

}

//assignment operator
Database & Database::operator=(const Database & aDatabase) {
    if(&aDatabase != this) {
		}
		return *this;
}




static int callback_static(
  //callback function that will be called by sqlite3_exec() for each
  //row in the query result table when the query has completed.
  void * a_Database, //pass through data provided to sqlite3_exec() [4th argument]
  int argc, //Number of columns in answer table row
  char ** argv, //array of strings representing table row values
  char ** azColName //array of strings representing column names
  ){
    Database* db = reinterpret_cast<Database*>(a_Database);
    return db->callback(argc, argv, azColName);
  }

int Database::callback(int argc, char **argv, char **azColName){
  for (int i = 0; i < argc; i++) {
    if (azColName[i]=="title" || azColName[i]=="artist" || azColName[i]=="composer"){
      returnString.append(toTitleCase(argv[i]));
    } else {
      returnString.append(argv[i]);
    }
    if(i!=argc-1){
      returnString.append(",");
    }
  }
  returnString.append("\n");
  recordCount++;
  return 0;
}


void Database::queryDatabase(string queryString){
	  //execute SQL queryString against the database
    returnString.erase();
    recordCount=0;
	  if(queryString.empty()) return;
	  const char * sqlQuery = queryString.c_str();
      rc = sqlite3_exec(db, sqlQuery, callback_static, this, &zErrMsg);
      if( rc != SQLITE_OK) {
          returnString.append("ERROR EXECUTING SQL: ").append(zErrMsg).append("\n");
          sqlite3_free(zErrMsg);
      }
      else {
         //returnString.append("SQL QUERY SUCCEEDED.");
      }
 }



//Getters
string Database::getDbfilename(){
  return dbfilename;
}






//Add things
string Database::addRecording(string a_recording_id, string a_title, string an_artist, string a_producer, string a_year){
  //if not already exists, add
  queryDatabase("select * from recordings where id='"+a_recording_id+"'");
  if (recordCount!=0){
    return "Error: Recording ID already exists. Please check command.\n";
  }
  queryDatabase("insert into recordings (id,title,artist,year,producer) values ('"+a_recording_id+"','"+a_title+"','"+an_artist+"','"+a_year+"','"+a_producer+"');");
  if (rc==0){
    return "Recording added.\n";
  } else {
    return(returnString);
  }
}
string Database::addSong(string a_song_id, string a_title, string a_composer){
  //if not already exists, add
  queryDatabase("select * from songs where sid='"+a_song_id+"'");
  if (recordCount!=0){
    return "Error: Song ID already exists. Please check command.\n";
  }
  queryDatabase("insert into songs (sid,title,composer) values ('"+a_song_id+"','"+a_title+"','"+a_composer+"');");
  if (rc==0){
    return "Song added.\n";
  } else {
    return(returnString);
  }
}
string Database::addTrack(string a_track_id, string a_recording_id, string a_song_id, string a_track_number){
  //if not already exists, add
  queryDatabase("select * from tracks where tid='"+a_track_id+"'");
  if (recordCount!=0){
    return "Error: Track ID already exists. Please check command.\n";
  }
  queryDatabase("insert into tracks (tid,albumID,songID,track_number) values ('"+a_track_id+"','"+a_recording_id+"','"+a_song_id+"','"+a_track_number+"');");
  if (rc==0){
    return "Track added.\n";
  } else {
    return(returnString);
  }
}
string Database::addUser(string a_user_id, string a_name){
  //if not already exists, add
  queryDatabase("select * from users where user_id='"+a_user_id+"'");
  if (recordCount!=0){
    return "Error: User ID already exists. Please check command.\n";
  }
  queryDatabase("insert into users (user_id,name) values ('"+a_user_id+"','"+a_name+"');");
  if (rc==0){
    return "User added.\n";
  } else {
    return(returnString);
  }
}
string Database::addPlaylist(string a_user_id, string a_playlist_name){
  //if not already exists, add
  queryDatabase("select * from playlists where user_id='"+a_user_id+"' and playlist_name='"+a_playlist_name+"'");
  if (recordCount!=0){
    return "Error: PLaylist name already exists for user. Please check command.\n";
  }
  queryDatabase("insert into playlists (user_id,playlist_name) values ('"+a_user_id+"','"+a_playlist_name+"');");
  if (rc==0){
    return "Playlist added.\n";
  } else {
    return(returnString);
  }
}
string Database::addTrackToPlaylist(string a_user_id, string a_playlist_name, string a_track_id){
  queryDatabase("insert into playlist_tracks (user_id,playlist_name,track_id) values ('"+a_user_id+"','"+a_playlist_name+"','"+a_track_id+"');");
  if (rc==0){
    return "Playlist added.\n";
  } else {
    return(returnString);
  }
}

//Single record Deletes
string Database::deleteSong(string a_song_id){
  //delete all tracks with song id, delete song if exists
  queryDatabase("select * from songs where sid='"+a_song_id+"'");
  if (recordCount==0){
    return "Error: Song ID does not exist. Please check command.\n";
  }
  queryDatabase("delete from songs where sid='"+a_song_id+"';");
  if (rc==0){
    return "Song removed.\n";
  } else {
    return(returnString);
  }
}
string Database::deleteRecording(string a_recording_id){
  //Delete all tracks with that recording_id, delete recording if exists
  queryDatabase("select * from recordings where id='"+a_recording_id+"'");
  if (recordCount==0){
    return "Error: Recording ID does not exist. Please check command.\n";
  }
  queryDatabase("delete from recordings where id='"+a_recording_id+"';");
  if (rc==0){
    return "Recording removed.\n";
  } else {
    return(returnString);
  }
}
string Database::deleteTrack(string a_track_id){
  //Remove track from all playlists, delete track if exists
  queryDatabase("select * from tracks where tid='"+a_track_id+"'");
  if (recordCount==0){
    return "Error: Track ID does not exist. Please check command.\n";
  }
  queryDatabase("delete from tracks where tid='"+a_track_id+"';");
  if (rc==0){
    return "Track removed.\n";
  } else {
    return(returnString);
  }
}
string Database::deleteUser(string a_user_id){
  //Remove all playlists with that user_id, delete user if exists
  queryDatabase("select * from users where user_id='"+a_user_id+"'");
  if (recordCount==0){
    return "Error: User ID does not exist. Please check command.\n";
  }
  queryDatabase("delete from users where user_id='"+a_user_id+"'");
  if (rc==0){
    return "User removed.\n";
  } else {
    return(returnString);
  }
}
string Database::deletePlaylist(string a_user_id, string a_playlist_name){
  //delete playlist if exists
  queryDatabase("select * from playlists where user_id='"+a_user_id+"' and playlist_name='"+a_playlist_name+"'");
  if (recordCount==0){
    return "Error: Playlist name does not exist for user. Please check command.\n";
  }
  queryDatabase("delete from playlists where user_id='"+a_user_id+"' and playlist_name='"+a_playlist_name+"'");
  if (rc==0){
    return "Playlist removed.\n";
  } else {
    return(returnString);
  }
}
string Database::removeTrackFromPlaylist(string a_user_id, string a_playlist_name, string a_track_id){
  //check if playlist exists, remove track if exists
  queryDatabase("select * from playlist_tracks where user_id='"+a_user_id+"' and playlist_name='"+a_playlist_name+"' and track_id='"+a_track_id+"'");
  if (recordCount==0){
    return returnString;
    return "Error: Track ID does not exist for playlist. Please check command.\n";
  }
  queryDatabase("delete from playlist_tracks where user_id='"+a_user_id+"' and playlist_name='"+a_playlist_name+"' and track_id='"+a_track_id+"'");
  if (rc==0){
    return "Track removed from playlist.\n";
  } else {
    return(returnString);
  }
}

//Sanity Deletes (multi Deletes)
string Database::deleteTracksBySongID(string a_song_id){
  queryDatabase("select * from tracks where sid='"+a_song_id+"'");
  int deletedRecordCount=recordCount;
  queryDatabase("delete from tracks where sid='"+a_song_id+"'");
  if (rc==0){
    return deletedRecordCount+" tracks deleted.\n";
  } else {
    return(returnString);
  }
}
string Database::deleteTracksByRecordingID(string a_recording_id){
  queryDatabase("select * from tracks where albumID='"+a_recording_id+"'");
  int deletedRecordCount=recordCount;
  queryDatabase("delete from tracks where albumID='"+a_recording_id+"'");
  if (rc==0){
    return deletedRecordCount+" tracks deleted.\n";
  } else {
    return(returnString);
  }
}
string Database::deletePlaylistTracksByTrackID(string a_track_id){
  queryDatabase("select * from playlist_tracks where track_id='"+a_track_id+"'");
  int deletedRecordCount=recordCount;
  queryDatabase("delete from playlist_tracks where track_id='"+a_track_id+"'");
  if (rc==0){
    return deletedRecordCount+" tracks deleted.\n";
  } else {
    return(returnString);
  }
}
string Database::deletePlaylistsByUserID(string a_user_id){
  queryDatabase("select * from playlists where user_id='"+a_user_id+"'");
  int deletedRecordCount=recordCount;
  queryDatabase("delete from playlists where user_id='"+a_user_id+"'");
  if (rc==0){
    return deletedRecordCount+" playlists deleted.\n";
  } else {
    return(returnString);
  }
}



string Database::listAllSongs(){
  queryDatabase("select title || ' by ' || composer from songs");
  return "Songs:\n"+returnString;
}
string Database::listAllUsers(){
  queryDatabase("select user_id || ': ' || name from users");
  return "Users:\n"+returnString;
}
string Database::listAllTracks(){
  queryDatabase("select tracks.track_number || ' from ' || recordings.title from tracks inner join recordings on tracks.albumID=recordings.id");
  return "Tracks:\n"+returnString;
}
string Database::listAllRecordings(){
  queryDatabase("select title || ' by ' || artist || ' (produced by ' || producer || ', ' || year || ')' from recordings");
  return "Recordings:\n"+returnString;
}
string Database::listSongsByPlaylist(string a_user_id,string a_playlist_name){
  //queryDatabase("select * from songs inner join tracks on songs.sid=tracks.songID inner join ");//playlists where user_id='"+a_user_id+"'");
  queryDatabase("select songs.title || ' by ' || songs.composer from songs inner join (tracks inner join playlist_tracks on tracks.tid = playlist_tracks.track_id) B on songs.sid = B.songID where B.user_id='"+a_user_id+"' and B.playlist_name='"+a_playlist_name+"'");
  return "Songs:\n"+returnString;
}
string Database::listPlaylistsByUser(string a_user_id){
  queryDatabase("select playlist_name from playlists where user_id='"+a_user_id+"'");
  return "Playlists:\n"+returnString;
}





string Database::toStr() const {
  return "Database: " + string(dbfilename) + "\n";
}

ostream & operator<<(ostream & out, const Database & p) {
   out << p.toStr();
   return out;
}
