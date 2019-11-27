//Author: Josh Chisholm (100770668)
//file log.cpp
#include <iostream>
#include <string>

using namespace std;

#include "sharedFunctions.h"

string toTitleCase(string inStr){
  if(inStr[0]=='"' && inStr.back()=='"'){
    inStr=inStr.substr(1,inStr.length()-2);//remove quotes from string
  }
  string outStr="";
  char prevChar=' ';//add space a beginning so first word isn't special case
  for (auto& iter : inStr){
    if((iter>='a' && iter<='z')&&prevChar==' '){
      outStr.push_back(toupper(iter));
    } else if((iter>='A' && iter<='Z')&&prevChar!=' ') {
      outStr.push_back(tolower(iter));
    } else {
      outStr.push_back(iter);
    }
    prevChar=iter;
  }
  //move the to end:
  if(outStr.substr(0,3)=="The"){
    outStr=outStr.substr(4)+", The";
  }
  return outStr;
}
