#include "searchresult.h"

SearchResult::SearchResult()
{
    // empty constructor
}

SearchResult::SearchResult(const std::string& prefix, const std::string& find, const std::string& suffix)
{
    const_cast<std::string&>(this->prefix) = prefix;
    const_cast<std::string&>(this->find) = find;
    const_cast<std::string&>(this->suffix) = suffix;
}

bool SearchResult::isEmpty()
{
    return prefix.empty() && find.empty() && suffix.empty();
}
