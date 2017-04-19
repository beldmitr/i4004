#include "commandset.h"

std::map<std::string, std::string> CommandSet::set
{
    { "NOP", "0000 0000" },
    { "JCN", "0001 CCCC AAAA AAAA" },
    { "FIM", "0010 PPP0 DDDD DDDD" },
    { "SRC", "0010 PPP1" },
    { "FIN", "0011 PPP0" },
    { "JIN", "0011 PPP1" },
    { "JUN", "0100 AAAA AAAA AAAA" },
    { "JMS", "0101 AAAA AAAA AAAA" },
    { "INC", "0110 RRRR" },
    { "ISZ", "0111 RRRR AAAA AAAA" },
    { "ADD", "1000 RRRR" },
    { "SUB", "1001 RRRR" },
    { "LD",  "1010 RRRR" },
    { "XCH", "1011 RRRR" },
    { "BBL", "1100 DDDD" },
    { "LDM", "1101 DDDD" },
    { "WRM", "1110 0000" },
    { "WMP", "1110 0001" },
    { "WRR", "1110 0010" },
    { "WR0", "1110 0100" },
    { "WR1", "1110 0101" },
    { "WR2", "1110 0110" },
    { "WR3", "1110 0111" },
    { "SBM", "1110 1000" },
    { "RDM", "1110 1001" },
    { "RDR", "1110 1010" },
    { "ADM", "1110 1011" },
    { "RD0", "1110 1100" },
    { "RD1", "1110 1101" },
    { "RD2", "1110 1110" },
    { "RD3", "1110 1111" },
    { "CLB", "1111 0000" },
    { "CLC", "1111 0001" },
    { "IAC", "1111 0010" },
    { "CMC", "1111 0011" },
    { "CMA", "1111 0100" },
    { "RAL", "1111 0101" },
    { "RAR", "1111 0110" },
    { "TCC", "1111 0111" },
    { "DAC", "1111 1000" },
    { "TCS", "1111 1001" },
    { "STC", "1111 1010" },
    { "DAA", "1111 1011" },
    { "KBP", "1111 1100" },
    { "DCL", "1111 1101" }
};

bool CommandSet::isCommand(const std::string& command)
{
    return !(set.find(command) == set.end());
}

std::string CommandSet::getRule(const std::string& command)
{
    if (set.find(command) == set.end())
    {
        std::string msg = "CommandSet::Command " + command + " doesn't exist in CommandSet.";
        throw msg;
    }
    return String::trimStrong(set[command]);
}

unsigned int CommandSet::getCode(const std::string& command)
{
    std::string rule = getRule(command);

    for (unsigned int i = 0; i < rule.length(); i++)
    {
        if (rule[i] != '0' && rule[i] != '1')
        {
            rule[i] = '0';
        }
    }

    rule = "0b" + rule;

    return Number::getUInt(rule);
}

unsigned int CommandSet::getLength(const std::string& command)
{
    int code = getCode(command);
    return (code & 0xFF00) ? 2 : 1;
}

unsigned int CommandSet::getNumberOperands(const std::string& command)
{
    std::string rule = getRule(command);

    OperandType previousOperand = OperandType::NONE;

    unsigned int count = 0;

    for (unsigned int i = 0; i < rule.length(); i++)
    {
        if (previousOperand == OperandType::NONE &&
                (rule[i] == OperandType::CONDITION ||
                 rule[i] == OperandType::ADDRESS ||
                 rule[i] == OperandType::DATA ||
                 rule[i] == OperandType::PAIR ||
                 rule[i] == OperandType::REGISTER))
        {
            previousOperand = (OperandType)rule[i];
            count += 1;
        }
        else if (rule[i] != (int)previousOperand &&
                 (rule[i] == OperandType::CONDITION ||
                  rule[i] == OperandType::ADDRESS ||
                  rule[i] == OperandType::DATA ||
                  rule[i] == OperandType::PAIR ||
                  rule[i] == OperandType::REGISTER))
        {
            previousOperand = (OperandType)rule[i];
            count += 1;
        }
    }

    return count;
}

std::vector<CommandSet::OperandStruct> CommandSet::getOperands(const std::string& command)
{
    std::vector<OperandStruct> result;

    std::string rule = getRule(command);

    std::reverse(rule.begin(), rule.end());

    OperandType previousType = OperandType::NONE;

    unsigned int position = 0;
    unsigned int length = 0;

    for (unsigned int i = 0; i < rule.size(); i++)
    {
        if (rule[i] == OperandType::CONDITION
                || rule[i] == OperandType::ADDRESS
                || rule[i] == OperandType::DATA
                || rule[i] == OperandType::PAIR
                || rule[i] == OperandType::REGISTER)
        {
            if (rule[i] != (int)previousType)
            {
                if (previousType != OperandType::NONE)
                {
                    result.push_back(OperandStruct(position, length, previousType));
                    previousType = OperandType::NONE;
                    length = 0;
                }

                position = i;
                previousType = (OperandType)rule[i];
                length++;
            }
            else
            {
                length++;
            }
        }
        else
        {
            if (previousType != OperandType::NONE)
            {
                result.push_back(OperandStruct(position, length, previousType));
                previousType = OperandType::NONE;
                length = 0;
            }
        }
    }

    if (result.size() != getNumberOperands(command))
    {
        std::string msg = "CommandSet::Something wrong with OperandStruct";
        throw msg;
    }

    std::reverse(result.begin(), result.end());

    return result;
}

CommandSet::OperandType CommandSet::getOperandType(const std::string& command, unsigned int operandNumber)
{
    std::string rule = getRule(command);

    OperandType previousOperand = OperandType::NONE;

    unsigned int actualOperandNumber = 0;

    for (unsigned int i = 0; i < rule.length(); i++)
    {
        if (rule[i] != (int)previousOperand &&
                (rule[i] == OperandType::CONDITION ||
                 rule[i] == OperandType::ADDRESS ||
                 rule[i] == OperandType::DATA ||
                 rule[i] == OperandType::PAIR ||
                 rule[i] == OperandType::REGISTER))
        {
            if (actualOperandNumber == operandNumber)
            {
                return (OperandType)rule[i];
            }
            else
            {
                previousOperand = (OperandType)rule[i];
                actualOperandNumber++;
            }
        }
    }

    std::string msg = "CommandSet::There is no " + std::to_string(operandNumber) + " operand in a command " + command;
    throw msg;
}


