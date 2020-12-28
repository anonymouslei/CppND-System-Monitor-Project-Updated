#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <chrono>
#include <string>
#include <thread>
#include <vector>

#include "linux_parser.h"

const int NUM_CPU_STATES = 10;

enum CPUStates {
  S_USER = 0,
  S_NICE,
  S_SYSTEM,
  S_IDLE,
  S_IOWAIT,
  S_IRQ,
  S_SOFTIRQ,
  S_STEAL,
  S_GUEST,
  S_GUEST_NICE
};

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp
  void ReadStatesCPU(size_t *times);
  float getUtilization(size_t *entries1, size_t *entries2);
  size_t GetActiveTime(const size_t *times);
  size_t GetIdleTime(const size_t *times);

  // TODO: Declare any necessary private members
 private:
};

#endif