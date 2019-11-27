//Author: Josh Chisholm (100770668)
//file: database.h
#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <string>
using namespace std;

#include "sqlite3.h"

class Database {
  private:
    const char * dbfilename;
    char * zErrMsg;  //will be used for query error messages
    int rc; //return code
    const char * data; //data passed through to callback
    string returnString;
    sqlite3 *db;
    int recordCount;
  public:
    Database(string aDbfilename);
    ~Database();
    Database( const Database & aDatabase);
    Database & operator=(const Database & aDatabase);

    int callback(int argc, char **argv, char **azColName);

    void queryDatabase(string queryString);

    string getDbfilename();

    string toStr() const;
    string addRecording(string a_recording_id, string a_title, string an_artist, string a_producer, string a_year); //if not already exists, add
    string addSong(string a_song_id, string a_title, string a_composer); //if not already exists, add
    string addTrack(string a_track_id, string a_recording_id, string a_song_id, string a_track_number); //if not already exists, add
    string addUser(string a_user_id, string a_name); //if not already exists, add
    string addPlaylist(string a_user_id, string a_playlist_name); //if not already exists, add
    string addTrackToPlaylist(string a_user_id, string a_playlist_name, string a_track_id); //If playlist exists, add track

    string deleteSong(string a_song_id);//delete all tracks with song id, delete song if exists
    string deleteRecording(string a_recording_id);//Delete all tracks with that recording_id, delete recording if exists
    string deleteTrack(string a_track_id);//Remove track from all playlists, delete track if exists
    string deleteUser(string a_user_id);//Remove all playlists with that user_id, delete user if exists
    string deletePlaylist(string a_user_id, string a_playlist_name);//delete playlist if exists
    string removeTrackFromPlaylist(string a_user_id, string a_playlist_name, string a_track_id);//check if playlist exists, remove track if exists

    string deleteTracksBySongID(string a_song_id);
    string deleteTracksByRecordingID(string a_recording_id);
    string deletePlaylistTracksByTrackID(string a_track_id);
    string deletePlaylistsByUserID(string a_user_id);

    string listAllSongs();
    string listAllUsers();
    string listAllTracks();
    string listAllRecordings();
    string listSongsByPlaylist(string a_user_id,string a_playlist_name);
    string listPlaylistsByUser(string a_user_id);

};

#endif
