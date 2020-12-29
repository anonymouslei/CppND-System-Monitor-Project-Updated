#include <string>

#include "format.h"

// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long seconds) {
  int HH, MM, SS;
  MM = seconds / 60;
  SS = seconds % 60;
  HH = MM / 60;
  MM = MM % 60;
  std::ostringstream elapsedTime;
  elapsedTime << std::setw(2) << std::setfill('0') << HH << ":" << std::setw(2)
              << std::setfill('0') << MM << ":" << std::setw(2)
              << std::setfill('0') << SS;
  return elapsedTime.str();
}