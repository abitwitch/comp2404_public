//Author: Josh Chisholm (100770668)
//file song.cpp
#include <iostream>
#include <string>
#include <fstream>

#include "song.h"

using namespace std;

//constructor
Song::Song(string a_song_id, string a_title, string a_composer):
  song_id(a_song_id),
  title(a_title),
  composer(a_composer)
  {
    //body of constructor
  }


//destructor
Song::~Song(){
  //todo
}

//copy constructor
Song::Song( const Song & aSong) {
		song_id = aSong.song_id;
    title = aSong.title;
    composer = aSong.composer;
}

//assignment operator
Song & Song::operator=(const Song & aSong) {
    if(&aSong != this) {
      song_id = aSong.song_id;
      title = aSong.title;
      composer = aSong.composer;
		}
		return *this;
}

//getters
string Song::getId(){
  return song_id;
}
string Song::getTitle(){
  return title;
}



string Song::toStr() const {
  return "Song: " + title + " composed by " + composer + "\n";
}

ostream & operator<<(ostream & out, const Song & p) {
   out << p.toStr();
   return out;
}
