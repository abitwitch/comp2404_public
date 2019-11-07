//Author: Josh Chisholm (100770668)
//file track.cpp
#include <iostream>
#include <string>
#include <fstream>

#include "track.h"

using namespace std;

//constructor
Track::Track(string a_track_id, string a_recording_id, string a_song_id, string a_track_number):
  track_id(a_track_id),
  recording_id(a_recording_id),
  song_id(a_song_id),
  track_number(a_track_number)
  {
    //body of constructor
  }


//destructor
Track::~Track(){
  //todo
}

//copy constructor
Track::Track( const Track & aTrack) {
		track_id = aTrack.track_id;
    recording_id = aTrack.recording_id;
    song_id = aTrack.song_id;
    track_number = aTrack.track_number;
    mp3_filename = aTrack.mp3_filename;
}

//assignment operator
Track & Track::operator=(const Track & aTrack) {
    if(&aTrack != this) {
      track_id = aTrack.track_id;
      recording_id = aTrack.recording_id;
      song_id = aTrack.song_id;
      track_number = aTrack.track_number;
      mp3_filename = aTrack.mp3_filename;
		}
		return *this;
}

//getters
string Track::getId(){
  return track_id;
}

string Track::getSong_id(){
  return song_id;
}

string Track::getRecording_id(){
  return recording_id;
}

string Track::getTrack_number(){
  return track_number;
}

string Track::toStr() const {
  return "Track: " + track_number + "\n";
}

ostream & operator<<(ostream & out, const Track & p) {
   out << p.toStr();
   return out;
}
