#include "data.h"



unsigned int Data::getUInt(const std::string& data)
{
    if (Number::isNumber(data))
    {
        return Number::getUInt(data);
    }
    else if (MathExpr::isMathExpression(data))
    {
        std::string s = Number::replaceNumbersWithDec(data);
        return MathExpr::evaluate(s);
    }
    else if (Constant::isLabel(data))
    {
        return Constant::getByName(data);
    }
    else
    {
        std::string msg = "There is wrong data " + data;
        throw CompilerException("Data", msg);
    }
}
