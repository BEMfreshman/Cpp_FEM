#ifndef UTILFUNCTION_H
#define UTILFUNCTION_H

#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

void trim(std::string& StrInput);


void SplitString(const std::string& StrInput,char SperateChar,
                 std::vector<std::string>& ans);

#endif // UTILFUNCTION_H
