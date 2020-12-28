#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() 
{
    return pId_;
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() 
{
  string utime, stime, cutime, cstime, starttime;
  string line, s_pid, tmp;
  long f_utime, f_stime, f_cutime, f_cstime;
  float utilization;
  s_pid = to_string(pId_);
  std::ifstream filestream(LinuxParser::kProcDirectory + string{"/"} +
                           s_pid + LinuxParser::kStatFilename);
 
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    for(auto i = 1; i < 14; i++)
    {
        linestream >> tmp;
    }
    linestream >> utime >> stime >> cutime >> cstime;
    for(auto i = 18; i < 22; i++)
    {
        linestream >> tmp;
    }
    linestream >> starttime;
  }
  f_utime = std::stol(utime, nullptr, 10);
  f_stime = std::stol(stime, nullptr, 10);
  f_cutime = std::stol(cutime, nullptr, 10);
  f_cstime = std::stol(cstime, nullptr, 10);
  startTime_ = std::stol(starttime, nullptr, 10);

  utilization = calCPUUsage(f_utime, f_stime, f_cutime, f_cstime, startTime_);

  return utilization;
}

float Process::calCPUUsage(long utime, long stime, long cutime, long cstime, long starttime)
{
    float total_time = (utime + stime + cutime + cstime)/ sysconf(_SC_CLK_TCK);
    
    float seconds = LinuxParser::UpTime() - (starttime / sysconf(_SC_CLK_TCK));

    return total_time/seconds;
}

// TODO: Return the command that generated this process
string Process::Command()
{
  string line, s_pid, cmdline;
  s_pid = to_string(pId_);
  std::ifstream filestream(LinuxParser::kProcDirectory + string{"/"} +
                           s_pid + LinuxParser::kCmdlineFilename);
 
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> cmdline;
  }
  return cmdline;
}

// TODO: Return this process's memory utilization
string Process::Ram() 
{
  size_t sz;
  string s_ram = LinuxParser::Ram(pId_);
  cpuRam_ = stol(s_ram, &sz);
  return std::to_string(stoi(LinuxParser::Ram(pId_))/1024);
}

// TODO: Return the user (name) that generated this process
string Process::User()
{
  // user
  string userId = LinuxParser::Uid(pId_);
  return LinuxParser::User(userId);
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() 
{

  return startTime_ / sysconf(_SC_CLK_TCK);
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator>(Process const& a) const 
{
  return cpuRam_ > a.cpuRam_;
}
bool Process::operator<(Process const& a) const 
{
  return cpuRam_ < a.cpuRam_;
}