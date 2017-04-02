#ifndef ERROR_H
#define ERROR_H

#include <string>

using namespace std;    /// TODO delete using namespace std

/// TODO Implement this class or understand why do we need it
class Error
{
public: /// TODO maybe better to make it private ??
    const int line;
    const string text;  /// TODO maybe to do it "const std::string&" ??
    const string command;   /// TODO maybe to do it "const std::string&" ??

public:
    Error(int line, string text, string command);
    virtual ~Error();
};

#endif // ERROR_H
