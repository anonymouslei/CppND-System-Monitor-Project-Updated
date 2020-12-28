#include <string>

#include "format.h"


std::string Format::Padding(string s, char c)
{
    s.insert(s.begin(), 2 - s.size(), c);
    return s;
}


string Format::ElapsedTime(long seconds) 
{
    int HH, MM, SS;
    MM = seconds / 60;
    SS = seconds % 60;
    HH = MM / 60;
    MM = MM % 60;
    return std::string(Format::Padding(std::to_string(HH), '0') + ":" + 
                       Format::Padding(std::to_string(MM), '0') + ":" + 
                       Format::Padding(std::to_string(SS), '0'));
}