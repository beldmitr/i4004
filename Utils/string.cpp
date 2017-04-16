#include "string.h"

std::string String::trimStrong(const std::string& str)
{
    return regex_replace(str, std::regex("([[:space:]]{1})"), "");
}

std::string String::trim(const std::string& str)
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

std::vector<std::string> String::divideBy(const std::string& str, const std::string& divider)
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

SearchResult String::search(const std::string& where, std::regex pattern)
{
    std::smatch matchList;

    if(regex_search(where, matchList, pattern))
    {
        std::string prefix = matchList.prefix();
        std::string find = matchList[0];
        std::string suffix = matchList.suffix();

        return SearchResult(prefix, find, suffix);
    }

    return SearchResult();
}

std::string String::trimBeginEnd(const std::string& str)
{
    std::string result = str;
    SearchResult begin = search(str, std::regex("^([[:space:]]+)"));

    if (!begin.isEmpty())
    {
        result = begin.suffix;
    }

    SearchResult end = search(result, std::regex("([[:space:]]+)$"));
    if (!end.isEmpty())
    {
        result = end.prefix;
    }

    return result;
}
