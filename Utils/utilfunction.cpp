#include "utilfunction.h"

void trim(std::string& StrInput)
{
    if(StrInput.empty())
    {
        return;
    }
    else
    {
        StrInput.erase(0,StrInput.find_first_not_of(" "));
        StrInput.erase(StrInput.find_last_not_of(" ")+1);
    }
}

void SplitString(const std::string& StrInput,char SperateChar,
                 std::vector<std::string>& ans)
{
    std::string str = StrInput;
    trim(str);
    std::istringstream iss(str);
    for(std::string item;std::getline(iss,item,SperateChar);)
    {
        ans.push_back(item);
    }
}
