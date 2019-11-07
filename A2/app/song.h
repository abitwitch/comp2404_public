//Author: Josh Chisholm (100770668)
//file: song.h
#ifndef SONG_H
#define SONG_H

#include <iostream>
#include <string>
using namespace std;

class Song {
  private:
    string song_id;
    string title;
    string composer;
  public:
    Song(string a_song_id, string a_title, string a_composer);
    ~Song();
    Song( const Song & aSong);
    Song & operator=(const Song & aSong);
    string getId();
    string getTitle();
    string toStr() const;

};

ostream & operator<<(ostream & out, const Song & p);

#endif
