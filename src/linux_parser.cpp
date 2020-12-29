#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// An example of how to read data from the filesystem
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

// An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return version;
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

// Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  string line;
  string key;
  string memTotal, memFree, memAvailable, buffers, value;
  size_t sz;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "MemTotal") {
          memTotal = value;
        }
        if (key == "MemFree") {
          memFree = value;
        }
        if (key == "MemAvailable") {
          memAvailable = value;
        }
        if (key == "Buffers") {
          buffers = value;
          break;
        }
      }
    }
  }
  long lMemTotal = std::stol(memTotal, &sz);
  long lMemFree = std::stol(memFree, &sz);

  float totalUsedMemory = lMemTotal - lMemFree;

  return totalUsedMemory / static_cast<float>(lMemTotal);
}

// Read and return the system uptime
long LinuxParser::UpTime() {
  string time, line;
  long int_time;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> time;
  }
  size_t sz;
  int_time = std::stol(time, &sz);

  return int_time;
}

int LinuxParser::TotalProcesses() {
  string line;
  string key;
  string value;
  int int_value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") {
          int_value = std::stoi(value, nullptr, 10);
          return int_value;
        }
      }
    }
  }
  return int_value;
}

// Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  string line;
  string key;
  string value;
  int int_value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") {
          int_value = std::stoi(value, nullptr, 10);
          return int_value;
        }
      }
    }
  }
  return int_value;
}

string LinuxParser::Ram(int pid) {
  string line, key, vmSize, s_pid;
  s_pid = to_string(pid);
  std::ifstream filestream(LinuxParser::kProcDirectory + string{"/"} + s_pid +
                           LinuxParser::kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> vmSize) {
        if (key == "VmSize") {
          return vmSize;
        }
      }
    }
  }

  return string("0");
}

// Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) {
  string line, key, value, s_pid, userId;
  s_pid = to_string(pid);
  std::ifstream filestream(LinuxParser::kProcDirectory + string{"/"} + s_pid +
                           LinuxParser::kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "Uid") {
          return value;
        }
      }
    }
  }
  return value;
}

// Read and return the user associated with a process
string LinuxParser::User(string userId) {
  string username, tmp, key, line;
  std::ifstream stream(LinuxParser::kPasswordPath);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> username >> tmp >> key) {
        if (key == userId) {
          return username;
        }
      }
    }
  }
  return username;
}