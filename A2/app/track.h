//Author: Josh Chisholm (100770668)
//file: track.h
#ifndef TRACK_H
#define TRACK_H

#include <iostream>
#include <string>
using namespace std;

class Track {
  private:
    string track_id;
    string recording_id;
    string song_id;
    string track_number;
    string mp3_filename;
  public:
    Track(string a_track_id, string a_recording_id, string a_song_id, string a_track_number);
    ~Track();
    Track( const Track & aTrack);
    Track & operator=(const Track & aTrack);
    string getId();
    string toStr() const;
    string getSong_id();
    string getTrack_number();
    string getRecording_id();
};

ostream & operator<<(ostream & out, const Track & p);

#endif
