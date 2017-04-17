#include "condition.h"


unsigned int Condition::getUInt(const std::string& str)
{
    if (Number::isNumber(str))
    {
        return Number::getUInt(str);
    }
    else if (Label::isLabel(str))
    {
        return Constant::getByName(str);
    }
    else if (MathExpr::isMathExpression(str))
    {
        return MathExpr::evaluate(str);
    }
    else
    {
        std::string msg = "Condition::Wrong condition " + str;
        throw msg;
    }
}
