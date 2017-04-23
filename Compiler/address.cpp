#include "address.h"

unsigned int Address::getUInt(const std::string& addr)
{
    if (addr.compare("*") == 0)
    {
        return ObjectCode::getProgramCounter();
    }
    if (Number::isNumber(addr))
    {
        return Number::getUInt(addr);
    }
    else if (MathExpr::isMathExpression(addr))
    {
        return MathExpr::evaluate(addr);
    }
    else if (Constant::isConstant(addr))
    {
        return Constant::getByName(addr);
    }
    else
    {
        std::string msg = "Address " + addr + " is wrong";
        throw CompilerException("Address", msg);
    }
}
