//Author: Josh Chisholm (100770668)
//file recording.cpp
#include <iostream>
#include <string>
#include <fstream>

#include "recording.h"

using namespace std;

//constructor
Recording::Recording(string a_recording_id, string a_title, string an_artist, string a_producer, string a_year):
  recording_id(a_recording_id),
  title(a_title),
  year(a_year),
  artist(an_artist),
  producer(a_producer)
  {
    //body of constructor
  }

//destructor
Recording::~Recording(){
  //todo
}

//copy constructor
Recording::Recording( const Recording & aRecording) {
		recording_id = aRecording.recording_id;
    title = aRecording.title;
    year = aRecording.year;
    artist = aRecording.artist;
    producer = aRecording.producer;
}

//assignment operator
Recording & Recording::operator=(const Recording & aRecording) {
    if(&aRecording != this) {
      recording_id = aRecording.recording_id;
      title = aRecording.title;
      year = aRecording.year;
      artist = aRecording.artist;
      producer = aRecording.producer;
		}
		return *this;
}

//getters
string Recording::getId(){
  return recording_id;
}
string Recording::getTitle(){
  return title;
}

string Recording::toStr() const {
  return "Recording: " + title + " by " + artist + " - Produced by: " + producer + " (" + year + ")\n";
}

ostream & operator<<(ostream & out, const Recording & p) {
   out << p.toStr();
   return out;
}
