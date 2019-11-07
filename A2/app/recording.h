//Author: Josh Chisholm (100770668)
//file: recording.h
#ifndef RECORDING_H
#define RECORDING_H

#include <iostream>
#include <string>
using namespace std;

class Recording {
  private:
    string recording_id;
    string title;
    string year;
    string artist;
    string producer;
  public:
    Recording(string a_recording_id, string a_title, string an_artist, string a_producer, string a_year);
    ~Recording();
    Recording( const Recording & aRecording);
    Recording & operator=(const Recording & aRecording);
    string getId();
    string getTitle();
    string toStr() const;

};

ostream & operator<<(ostream & out, const Recording & p);

#endif
