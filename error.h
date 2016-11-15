#ifndef ERROR_H
#define ERROR_H

#include <string>

using namespace std;

class Error
{
public:
    const int line;
    const string text;
    const string command;

public:
    Error(int line, string text, string command);
};

#endif // ERROR_H
