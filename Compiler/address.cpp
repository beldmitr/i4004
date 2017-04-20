#include "address.h"

unsigned int Address::getUInt(const std::string& addr)
{
    if (Number::isNumber(addr))
    {
        return Number::getUInt(addr);
    }
    else if (MathExpr::isMathExpression(addr))
    {
        std::string s = Number::replaceNumbersWithDec(addr);
        return MathExpr::evaluate(s);
    }
    else if (Constant::isLabel(addr))
    {
        return Constant::getByName(addr);
    }
    else
    {
        std::string msg = "Address " + addr + " is wrong";
        throw CompilerException("Address", msg);
    }
}
