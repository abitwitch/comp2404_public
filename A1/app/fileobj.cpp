//Author: Josh Chisholm (100770668)
//file fileobj.cpp
#include <iostream>
#include <string>
#include <fstream>
#include "fileobj.h"
using namespace std;
//constructor
FileObj::FileObj(string inPath){
  path = inPath;
  contents="";
  accessible=false;
  ifstream file(path, ifstream::in);
	if(file){
		accessible=true;
	}else{
    //cout << "Warning: could not open file " << path << ".\n";
  }
  file.close();
}
//destructor
FileObj::~FileObj(){

}


//functions
string FileObj::read(){
  ifstream file(path, ifstream::in);
  accessible=!(!file);//convert to boolean
  if(!accessible){
    cout << "ERROR: could not open file " << path << "  ...exiting\n";
    return "";
  }
  string input;
  contents="";
  while(getline(file, input)){
		contents += input+"\n";
	}
  file.close();
  return contents;
}
