#include "address.h"


unsigned int Address::getActual() const
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
        return MathExpr::evaluate(addr);
    }
    else if (Label::isLabel(addr))
    {
        return LabelTable::getByName(addr);
    }
    else
    {
        std::string msg = "Address::Address " + addr + " is wrong";
        throw msg;
    }
}
