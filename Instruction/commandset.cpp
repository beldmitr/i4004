#include "commandset.h"

std::map<std::string, unsigned int> Instruction::CommandSet::set
{
    { "NOP", 0x0},
    { "JCN", 0x1000 },
    { "FIM", 0x2000 },
    { "SRC", 0x21 },
    { "FIN", 0x30 },
    { "JIN", 0x31 },
    { "JUN", 0x4000 },
    { "JMS", 0x5000 },
    { "INC", 0x60 },
    { "ISZ", 0x7000 },
    { "ADD", 0x80 },
    { "SUB", 0x90 },
    { "LD", 0xA0 },
    { "XCH", 0xB0 },
    { "BBL", 0xC0 },
    { "LDM", 0xD0 },
    { "WRM", 0xE0 },
    { "WMP", 0xE1 },
    { "WRR", 0xE2 },
    { "WR0", 0xE4 },
    { "WR1", 0xE5 },
    { "WR2", 0xE6 },
    { "WR3", 0xE7 },
    { "SBM", 0xE8 },
    { "RDM", 0xE9 },
    { "RDR", 0xEA },
    { "ADM", 0xEB },
    { "RD0", 0xEC },
    { "RD1", 0xED },
    { "RD2", 0xEE },
    { "RD3", 0xEF },
    { "CLB", 0xF0 },
    { "CLC", 0xF1 },
    { "IAC", 0xF2 },
    { "CMC", 0xF3 },
    { "CMA", 0xF4 },
    { "RAL", 0xF5 },
    { "RAR", 0xF6 },
    { "TCC", 0xF7 },
    { "DAC", 0xF8 },
    { "TCS", 0xF9 },
    { "STC", 0xFA },
    { "DAA", 0xFB },
    { "KBP", 0xFC },
    { "DCL", 0xFD }
};
// TODO 46. command ???
// TODO check numbers of instructions, (for example if 0xFD equals to DCL command, so make a test)

bool Instruction::CommandSet::isCommand(const std::string& command)
{
    return !(set.find(command) == set.end());
}

unsigned int Instruction::CommandSet::getCommand(const std::string& command)
{
    if (set.find(command) == set.end())
    {
        std::string msg = "CommandSet::Command " + command + " doesn't exist in CommandSet.";
        throw msg;
    }

    return set[command];
}

unsigned int Instruction::CommandSet::getLength(const std::string& command)
{
    int code = getCommand(command);
    return (code & 0xFF00) ? 2 : 1;
}
