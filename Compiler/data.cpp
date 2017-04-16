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
    else if (Label::isLabel(data))
    {
        return LabelTable::getByName(data);
    }
    else
    {
        std::string msg = "Data::There is wrong data " + data;
        throw msg;
    }
}
