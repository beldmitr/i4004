#include "condition.h"


unsigned int Condition::getUInt(const std::string& str)
{
    if (Number::isNumber(str))
    {
        return Number::getUInt(str);
    }
    else if (Constant::isConstant(str))
    {
        return Constant::getByName(str);
    }
    else if (MathExpr::isMathExpression(str))
    {
        return MathExpr::evaluate(str);
    }
    else
    {
        std::string msg = "Wrong condition " + str;
        throw CompilerException("Condition", msg);
    }
}
