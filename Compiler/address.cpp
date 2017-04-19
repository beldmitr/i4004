#include "address.h"

unsigned int Address::actual = 0;

unsigned int Address::getActual()
{
    return actual;
}

void Address::setActual(unsigned int addr)
{
    actual = addr;
}

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
        std::string msg = "Address::Address " + addr + " is wrong";
        throw msg;
    }
}
