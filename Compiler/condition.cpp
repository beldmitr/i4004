#include "condition.h"


unsigned int Condition::getUInt(const std::string& str)
{
    if (Number::isNumber(str))
    {
        return Number::getUInt(str);
    }
    else if (Constant::isLabel(str))
    {
        return Constant::getByName(str);
    }
    else if (MathExpr::isMathExpression(str))
    {
        std::string s = Number::replaceNumbersWithDec(str);
        return MathExpr::evaluate(s);
    }
    else
    {
        std::string msg = "Wrong condition " + str;
        throw CompilerException("Condition", msg);
    }
}
