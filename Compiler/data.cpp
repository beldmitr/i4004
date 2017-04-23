#include "data.h"



unsigned int Data::getUInt(const std::string& data)
{
    if (Number::isNumber(data))
    {
        return Number::getUInt(data);
    }
    else if (MathExpr::isMathExpression(data))
    {
        return MathExpr::evaluate(data);
    }
    else if (Constant::isConstant(data))
    {
        return Constant::getByName(data);
    }
    else
    {
        std::string msg = "There is wrong data " + data;
        throw CompilerException("Data", msg);
    }
}
