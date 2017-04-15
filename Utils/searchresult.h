#ifndef SEARCHRESULT_H
#define SEARCHRESULT_H

#include <string>

class SearchResult
{
public:
    const std::string prefix;
    const std::string find;
    const std::string suffix;

    SearchResult();
    SearchResult(const std::string& prefix, const std::string& find, const std::string& suffix);

    bool isEmpty();

};

#endif // SEARCHRESULT_H
