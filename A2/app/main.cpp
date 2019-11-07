//Author: Josh Chisholm (100770668)
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <sstream>


#include "fileobj.h"
#include "log.h"
#include "recording.h"
#include "track.h"
#include "song.h"
#include "playlist.h"
#include "user.h"
#include "dal.h"


using namespace std;

//Global variables
Log log;
Dal dal;


//Control screen output and loggin method:
struct LogStream
{
    template<typename T> LogStream& operator<<(const T& mValue)
    {
        cout << mValue;
        if(log.getLogOuts()){
          log.add(string(mValue));
        }
    }
};

inline LogStream& lo() { static LogStream l; return l; }

//Other methods
string trim(string &input, bool trimInsideString){
  size_t start=input.find_first_not_of(" \t");
  size_t end=input.find_last_not_of(" \t");
  if(string::npos==start){
    return input;
  }
  input=input.substr(start,(end-start+1));
  if (trimInsideString){
    string tempStrHolder="";
    char prevChar=input[0];
    for (auto& iter : input){
      if(prevChar==' '&&iter==' '){
        //skip all subsiquent spaces
      }else{
        tempStrHolder.push_back(iter);
      }
      prevChar=iter;
    }
    input=tempStrHolder;
  }
  return input;
}

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

vector<string> parse(string input){
  vector<string> args;
  bool inStr=false;
  int index=0;
  int startIndex=0;
  int argLength=0;
  for (auto& iter : input){
    if (iter=='"'){
      inStr=!inStr;
    }
    if (!inStr){
      if (iter==' '||index+1==input.length()){
        if (index+1==input.length()){
          argLength+=1;
        }
        string arg=input.substr(startIndex,argLength);
        if(arg.rfind("\"", 0) == 0){
          arg=arg.substr(1,arg.size()-2);//remove quotes
          arg=toTitleCase(arg); //TODO don't title case every string.
        }
        args.push_back(arg);
        startIndex=index+1;
        argLength=-1;
      }
    }
    index++;
    argLength++;
  }
  if (inStr){
    lo() << "Invalid input detected: " << input << "\n";
  }
  return args;
}

void printVectorStr (vector<string> args){
  lo() << "Parsed command arguments:\n";
  vector<string>::iterator i;
  for (i=args.begin();i<args.end();i++){
    lo() << "  -" << *i <<"\n";
  }
}

bool startsWith(string fullStr, string prefix){
  fullStr=fullStr.substr(1,fullStr.length()-2);//remove quotes from string
  prefix=prefix.substr(1,prefix.length()-2);//remove quotes from string
  if(fullStr.length()<prefix.length()){
    return false;
  }
  if(fullStr.substr(0,prefix.length())==prefix){
    return true;
  } else {
    return false;
  }
}
bool endsWith(string fullStr, string prefix){
  fullStr=fullStr.substr(1,fullStr.length()-2);//remove quotes from string
  prefix=prefix.substr(1,prefix.length()-2);//remove quotes from string
  if(fullStr.length()<prefix.length()){
    return false;
  }
  if(fullStr.substr(fullStr.length()-prefix.length(),prefix.length())==prefix){
    return true;
  } else {
    return false;
  }
}

int main(void){
  //Welcome
  string welcomeStr=R"(
  +========================================+
  |                                        |
  |           Welcome to jTunes            |
  |                                        |
  +========================================+
  |  '>>>' is prompting you for a command  |
  |  At any time you can type:             |
  |    -> '.help' for help                 |
  |    -> '.quit' to quit                  |
  +========================================+)";
  lo() << welcomeStr << "\n\n";

  //Local variables
  string input;
  queue<string> readInputs;
  bool isUserInput;

  //Testing area
  //To test a command use: readInputs.push("command");
  //Example: readInputs.push("add -u gob \"George Oscar Bluth\"");

  //Testing area

  while(input!=".quit"){
    //=====get user input or input from read:=====
    if(log.getLogCmds()){
      lo() << ">>>";
    } else {
      cout << ">>>";
    }
    if (!readInputs.empty()){
      input=readInputs.front();
      readInputs.pop();
      isUserInput=false;
    } else {
      getline(cin, input);
      isUserInput=true;
    }
    if(log.getLogCmds()){
      log.add(input);
      log.add("\n");
    }
    //=====clean up user input:=====
    bool trimInsideString=true;
    trim(input, trimInsideString);
    //TODO remove case sensitivity?
    //=====skip for empty input:=====
    if(input==""){
      continue;
    }
    //=====parse user input:=====
    vector<string> args=parse(input);

    if (args[0].length()!=0 && input.at(0)=='.'){
      //=====pull out UI SHELL COMMANDS (start with a dot):=====
      if (input==".quit"){
        //-----quit-----
        lo() << "Exiting program. Goodbye!";
        continue; //the while loop will exit with ".quit"
      } else if (args[0]==".read") {
        //-----read-----
        FileObj file(args[1]);
        string contents=file.read();
        std::stringstream strStream(contents);
        std::string line;

        while(std::getline(strStream,line,'\n')){
          if (trim(line, false)!=""){
            if(line[0]!='.') {
              readInputs.push(line);
            }
          }
        }

      } else if (args[0]==".log") {
        //-----log-----
        string updateCmd="";
        if (args.size()>1){
          updateCmd=args[1];
        }
        string logFileName="";
        if (args.size()>2){
          logFileName=args[2];
        }
        lo() << log.updateLogging(updateCmd,logFileName);
      } else if (input==".help") {
        //-----help-----
        FileObj file("help.txt");
        lo() << file.read();
      }
      //=====Developer commands:=====
      else if (args[0]==".trim") {
        //-----trim-----
        string args1_noQuotes=args[1].substr(1,args[1].length()-2);//remove quotes from string
        lo() << trim(args1_noQuotes,true) << "\n";
      } else if (args[0]==".startsWith") {
        //-----startsWith-----
        if(startsWith(args[1],args[2])){
          lo() << "true\n";
        } else {
          lo() << "false\n";
        }
      } else if (args[0]==".endsWith") {
        //-----endsWith-----
        if(endsWith(args[1],args[2])){
          lo() << "true\n";
        } else {
          lo() << "false\n";
        }
      } else if (args[0]==".toTitleCase") {
        //-----toTitleCase-----
        lo() << toTitleCase(args[1]) << "\n";
      }
      //=====Unknown UI Shell Command (start with a dot):=====
      else {
        lo() << "Unknown UI Shell Command: \"" << input << "\"\n";
      }
    }
    //=====Comments:=====
    else if (input.length()>=2 && input.substr(0,2)=="//") {
      //-----comment-----
      if(!isUserInput){
        lo() << input;
        lo() << "\n";
      }else{
        log.add(input);
        log.add("\n");
      }
    }
    //=====Other Commands:=====
    else {
      if (args[0]=="add") {
        lo() << dal.addObj(args);
        //printVectorStr(args);
      } else if (args[0]=="delete") {
        lo() << dal.deleteObj(args);
        //printVectorStr(args);
      } else if (args[0]=="show") {
        lo() << dal.showObj(args);
        //printVectorStr(args);
      } else {
        //=====Unknown Command:=====
        lo() << "Unknown Command: \"" << input << "\"\n";
      }
    }

  }

  lo() << "\n";
  return 0;
}
