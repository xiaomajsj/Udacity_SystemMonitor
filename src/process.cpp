#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"
#include "system.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() const{ 
   return pid;
    }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() const { 
  long total_time;
  long second;
  float cpu_usage;
  long SystemUptime;
  std::vector<long> ProcUtili;

  ProcUtili=LinuxParser::ProcessUtilization(Pid());
  total_time=ProcUtili[ProcessUtili::uTime]+ProcUtili[ProcessUtili::sTime]+ProcUtili[ProcessUtili::cuTime]+ProcUtili[ProcessUtili::csTime];
  SystemUptime=LinuxParser::UpTime();
  second=SystemUptime-(ProcUtili[ProcessUtili::startTime]/sysconf(_SC_CLK_TCK));
  cpu_usage=(((float)(total_time/sysconf(_SC_CLK_TCK)))/(float)second);

  return cpu_usage;
  
 }

// TODO: Return the command that generated this process
string Process::Command() { 
    return LinuxParser::Command(Pid());
    }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(Pid());}

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(Pid());}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(Pid()); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
    return (this->CpuUtilization() > a.CpuUtilization());
 }