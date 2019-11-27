//Author: Josh Chisholm (100770668)
//file: log.h
#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <string>
using namespace std;

class Log {
  private:
    bool logCmds;
    bool logOuts;
    string logFileName;
    string contents;
  public:
    Log();
    ~Log();
    bool getLogCmds();
    void setLogCmds(bool setTo);
    bool getLogOuts();
    void setLogOuts(bool setTo);
    string getLogFileName();
    void setLogFileName(string setTo);
    void add(string str);
    string getContents();
    void save();
    string updateLogging(string updateCmd, string newLogFileName);
};
#endif
