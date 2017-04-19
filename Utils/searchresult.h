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

    SearchResult& operator=(SearchResult other)
    {
        const_cast<std::string&>(this->prefix) = other.prefix;
        const_cast<std::string&>(this->find) = other.find;
        const_cast<std::string&>(this->suffix) = other.suffix;

        return *this;
    }

    bool isEmpty();

};

#endif // SEARCHRESULT_H
