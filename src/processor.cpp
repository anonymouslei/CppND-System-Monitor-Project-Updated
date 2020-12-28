#include "processor.h"



// TODO: Return the aggregate CPU utilization
float Processor::Utilization() // reference: a C++ program to get CPU usage from command line in Linux
{
    size_t preTimes[NUM_CPU_STATES];
    size_t currTimes[NUM_CPU_STATES];

    // snapshot 1
    ReadStatesCPU(preTimes);

    // 100ms pause
    std::this_thread::sleep_for(std::chrono::milliseconds(90));

    // snapshot 2
    ReadStatesCPU(currTimes);

    return getUtilization(preTimes, currTimes);

}

void Processor::ReadStatesCPU(size_t *times)
{
  std::string line, cpu;
  std::ifstream stream(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> cpu;
    for (size_t i=0; i < NUM_CPU_STATES ; i++)
    {
        linestream >> times[i];
    }
  }
}

float Processor::getUtilization(size_t *entries1, size_t *entries2)
{
    const float activeTime = static_cast<float>(GetActiveTime(entries2) - GetActiveTime(entries1));
    const float idleTime = static_cast<float>(GetIdleTime(entries2) - GetIdleTime(entries1));
    const float totalTime = activeTime + idleTime; 

    return activeTime / totalTime;
}

size_t Processor::GetActiveTime(const size_t *times)
{
    return times[S_USER] +
           times[S_NICE] +
           times[S_SYSTEM] +
           times[S_IRQ] +
           times[S_SOFTIRQ] +
           times[S_STEAL] +
           times[S_GUEST] +
           times[S_GUEST_NICE];
}


size_t Processor::GetIdleTime(const size_t *times)
{
    return times[S_IDLE] + times[S_IOWAIT];
}