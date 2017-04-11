#include "string.h"

std::string Utils::String::trimStrong(const std::string& str)
{
    return regex_replace(str, std::regex("([[:space:]]{1})"), "");
}

std::string Utils::String::trim(const std::string& str)
{
    std::string res = regex_replace(str, std::regex("([[:space:]]+)"), " ");
    if (res.empty() || strcmp(res.c_str(), " ") == 0)
    {
        return "";
    }

    if (res.at(0) == ' ')
    {
        res.erase(0, 1);
    }

    if (res.at(res.length() - 1) == ' ')
    {
        res.erase(res.length() - 1, 1);
    }

    return res;
}

std::vector<std::string> Utils::String::divideBy(const std::string& str, const std::string& divider)
{
    std::vector<std::string> result;
    size_t beginPosition = 0;
    size_t findPosition = str.find(divider, beginPosition);
    result.push_back(str.substr(beginPosition, findPosition-beginPosition));

    while (findPosition != std::string::npos)
    {
        beginPosition = findPosition;
        findPosition = str.find(divider, beginPosition+1);

        result.push_back(str.substr(beginPosition+1, findPosition-beginPosition-1));
    }

    return result;
}
