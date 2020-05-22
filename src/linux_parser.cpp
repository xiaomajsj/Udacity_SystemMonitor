#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"


using std::stof;
using std::string;
using std::to_string;
using std::vector;

template <class Type>

Type stringToNum(string &str){
std::istringstream iss(str);
Type num;
iss>>num;
return num;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  string line;
  string key;
  string value;
  string KB;
  float MemTotal, MemFree, MemAvailable;
  std::ifstream filestream(kProcDirectory+kMeminfoFilename);
  if(filestream.is_open()){
   while(std::getline(filestream,line)){
     std::istringstream linestream(line);
     while(linestream>>key>>value>>KB){
     if(key=="MemTotal:"){
     MemTotal=stringToNum<float>(value);}
     else if(key=="MemFree:"){
     MemFree=stringToNum<float>(value);}
     else if(key=="MemAvailable:"){
     MemAvailable=stringToNum<float>(value);}
     }
   }
   return (MemTotal-MemFree)/MemTotal;
  }
  }

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  string Uptime;
  string SpendTime;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> Uptime >> SpendTime;
  }
  return stringToNum<long>(Uptime);


 }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  string value1,value2,value3,value4,value5,value6,value7,value8,value9,value10;
  string key;
  string line;
  vector<string> Output;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while(std::getline(stream, line)){
    std::istringstream linestream(line);
    linestream >> key >> value1>> value2>> value3>> value4>> value5>> value6>> value7>> value8>> value9>> value10;
    if(key=="cpu"){
      Output.push_back(value1);
      Output.push_back(value2);
      Output.push_back(value3);
      Output.push_back(value4);
      Output.push_back(value5);
      Output.push_back(value6);
      Output.push_back(value7);
      Output.push_back(value8);
      Output.push_back(value9);
      Output.push_back(value10);
      }
  }
  }
  return Output;
 }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string TotalPrcs;
  string key;
  string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while(std::getline(stream, line)){
    std::istringstream linestream(line);
    linestream >> key >> TotalPrcs;
    if(key=="processes"){return stringToNum<int>(TotalPrcs);}
  }
  }
 }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string RunningPrcs;
  string key;
  string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while(std::getline(stream, line)){
    std::istringstream linestream(line);
    linestream >> key >> RunningPrcs;
    if(key=="procs_running"){return stringToNum<int>(RunningPrcs);}
   }
  }
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
   string command;
   string line;
   std::ifstream stream(kProcDirectory + "/" + to_string(pid)+ kCmdlineFilename);
  if (stream.is_open()) {
    while(std::getline(stream, line)){
    std::istringstream linestream(line);
    linestream >> command;
    return command;
  }
 }
}




// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
   string memoryused;
   float memoryinM;
   string line;
   string key;
   string kb;
   std::ifstream stream(kProcDirectory + "/" + to_string(pid)+ kStatusFilename);
  if (stream.is_open()) {
    while(std::getline(stream, line)){
    std::istringstream linestream(line);
    while(linestream >> key>>memoryused>>kb){
    if(key=="VmSize:"){
      memoryinM=stringToNum<float>(memoryused)/1000;
      return to_string(memoryinM)+"mB";} 
    }
  }
 }

}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  string uid;
   string line;
   string key;
   std::ifstream stream(kProcDirectory + "/" + to_string(pid)+ kStatusFilename);
  if (stream.is_open()) {
    while(std::getline(stream, line)){
    std::istringstream linestream(line);
    linestream >> key>>uid;
    if(key=="Uid:"){return uid;} 
  }
 }
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
   string username;
   string line;
   string key;
   string key2;
   string uid;

   uid=Uid(pid);
   std::ifstream stream(kPasswordPath);
  if (stream.is_open()) {
    while(std::getline(stream, line)){
    std::replace(line.begin(),line.end(),':',' ');
    std::istringstream linestream(line);
    linestream >> username>>key2>>uid;
    if(key2=="x"){return username;} 
   }
 }
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
   string unused;
   string line;
   string Uptime;

   std::ifstream stream(kProcDirectory + "/" + to_string(pid)+ kStatFilename);
  if (stream.is_open()) {
    while(std::getline(stream, line)){
    std::istringstream linestream(line);
    for(unsigned int i=0;i<21;i++){
      if(i==21){
    linestream >> Uptime;}
      else{linestream >> unused;}
      } 
    
    }
  }
 return stringToNum<long>(Uptime)/sysconf(_SC_CLK_TCK);
 }