#ifndef CONVERT_H
#define CONVERT_H

#include <string>
//#include "utils.h"
#include "Compiler/operand.h"

/// TODO delete unused headers
class Convert
{
public:
    static unsigned int register2uint(const std::string& str);
    static unsigned int pair2uint(const std::string& str);
    static int condition2int(const std::string& str);
    static int address2int(const std::string& str);
    static int bin2int(const std::string& str); //TODO bin2int
    static int hex2int(const std::string& str); //TODO hex2int
    static int dec2int(const std::string& str);
    static int to4bit(int num);
    static int to8bit(int num);
    static int to12bit(int num);
    static int to4bitStrong(int num);
    static int to8bitStrong(int num);
    static int to12bitStrong(int num);

};


#endif // CONVERT_H
