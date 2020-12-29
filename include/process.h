#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include "linux_parser.h"
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int id) : pId_(id){};
  int Pid();
  std::string User();
  std::string Command();
  float CpuUtilization();
  std::string Ram();
  long int UpTime();
  bool operator>(Process const& a) const;
  bool operator<(Process const& a) const;

  // Declare any necessary private members
 private:
  float calCPUUsage(long utime, long stime, long cutime, long cstime,
                    long starttime);

  int pId_;
  float cpuRam_;
};

#endif