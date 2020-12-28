#ifndef FORMAT_H
#define FORMAT_H

#include <string>

using std::string;

namespace Format {
std::string ElapsedTime(long times);  // TODO: See src/format.cpp
std::string Padding(string s, char c);
};                                    // namespace Format

#endif