//Author: Josh Chisholm (100770668)
//file log.cpp
#include <iostream>
#include <string>
#include <fstream>

#include "log.h"
#include "fileobj.h"

using namespace std;

//constructor
Log::Log(){
  logCmds=false;
  logOuts=false;
  logFileName="";
  contents="";
}
//destructor
Log::~Log(){

}



//getters and setters
bool Log::getLogCmds(){
  return logCmds;
}
void Log::setLogCmds(bool setTo){
  logCmds=setTo;
}
bool Log::getLogOuts(){
  return logOuts;
}
void Log::setLogOuts(bool setTo){
  logOuts=setTo;
}
string Log::getLogFileName(){
  return logFileName;
}
void Log::setLogFileName(string setTo){
  logFileName=setTo;
}

//Functions to manage contents
void Log::add(string str){
  contents.append(str);
}
string Log::getContents(){
  return contents;
}
void Log::save(){
  ofstream myfile;
  myfile.open (logFileName, std::ios::app);
  if(!myfile){
    cout << "ERROR: could not open file " << logFileName << "\n";
  } else {
    myfile << contents;
  }
  myfile.close();
}

//funtion to update log settings
string Log::updateLogging(string updateCmd, string newLogFileName){
  if(updateCmd=="clear"){
    contents.clear();
    return "Log cleared.\n";
  } else if (updateCmd=="start"){
    logCmds=true;
    logOuts=false;
    return "Started logging all commands.\n";
  } else if (updateCmd=="start_output"){
    logCmds=false;
    logOuts=true;
    return "Started logging all outputs.\n";
  } else if (updateCmd=="start_both"){
    logCmds=true;
    logOuts=true;
    return "Started logging all commands and outputs.\n";
  } else if (updateCmd=="stop"){
    logCmds=false;
    logOuts=false;
    return "Stopped all logging.\n";
  } else if (updateCmd=="save"){
    logFileName=newLogFileName;
    save();
    return "Log saved to file.\n";
    //return "Log file set to: ";.append(newLogFileName).append("\n");
  } else if (updateCmd=="show"){
    cout << "Contents of log file (this will not be logged): " << newLogFileName << "\n";
    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-Start of log-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
    cout << contents;
    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=End of log=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
    return "";
  } else {
    return "Unknown argument for .log command\n";
    //return "Unknown argument for .log command: \"";.append(updateCmd).append("\"\ntype .help for help.\n");
  }
}
