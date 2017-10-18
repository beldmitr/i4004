#include "debugger.h"

std::unordered_set<unsigned> Debugger::breakpointAddresses = std::unordered_set<unsigned>();

Debugger::Debugger(QObject *parent) : QObject(parent)
{

}

bool Debugger::hasNextByte(unsigned code)
{
    /*
     *  If it is a 2 byte instruction, read the next byte
     *  There are 5 instructions 2 byte long:
     *  Jump Conditional	JCN	0001CCCC	AAAAAAAA	condition, address
     *  Fetch Immediate     FIM	0010RRR0	DDDDDDDD	register pair, data
     *  Jump Uncoditional	JUN	0100AAAA	AAAAAAAA	address
     *  Jump to Subroutine	JMS	0101AAAA	AAAAAAAA	address
     *  Increment and Skip	ISZ	0111RRRR	AAAAAAAA	register, address
     *
     *  So we took a high byte with previous command
     *  and after we read the lowest byte.
     */

    return ((code & 0xF0) == 0x10    // JCN
            || (code & 0xF1) == 0x20 // FIM
            || (code & 0xF0) == 0x40     // JUN
            || (code & 0xF0) == 0x50     // JMS
            || (code & 0xF0) == 0x70);    // ISZ
}

QString Debugger::codeToInstruction(unsigned code)
{
    QString instruction = "";

    if ((code & 0xFFFF) == 0x0000) // NOP
    {
        instruction = "NOP";
    }
    else if ((code & 0xF000) == 0x1000) // JCN
    {
        instruction = "JCN 0x" + QString::number((code & 0x0F00) >> 8, 16) + ", "
                + "0x" + QString::number(code & 0x00FF, 16);
    }
    else if ((code & 0xF100) == 0x2000) // FIM
    {
        instruction = "FIM P" + QString::number((code & 0xE00) >> 9, 16) + ", "
                + "0x" + QString::number(code & 0xFF, 16);
    }
    else if ((code & 0xFFF1) == 0x0021) // SRC
    {
        instruction = "SRC P" + QString::number((code & 0x0E) >> 1, 16);
    }
    else if ((code & 0xFFF1) == 0x0030) // FIN
    {
        instruction = "FIN P" + QString::number((code & 0xE) >> 1, 16);
    }
    else if ((code & 0xFFF1) == 0x0031) // JIN
    {
        instruction = "JIN P" + QString::number((code & 0xE) >> 1, 16);
    }
    else if ((code & 0xF000) == 0x4000) // JUN
    {
        instruction = "JUN 0x" + QString::number((code & 0x0F00) >> 8, 16) + ", "
                + QString::number(code & 0x00FF, 16);
    }
    else if ((code & 0xF000) == 0x5000) // JMS
    {
        instruction = "JMS 0x" + QString::number((code & 0x0F00) >> 8, 16) + ", "
                + QString::number(code & 0x00FF, 16);
    }
    else if ((code & 0xFFF0) == 0x0060) // INC
    {
        instruction = "INC R" + QString::number(code & 0xF, 16);
    }
    else if ((code & 0xF000) == 0x7000) // ISZ
    {
        instruction = "ISZ R" + QString::number((code & 0x0F00) >> 8, 16) + ", "
                + "0x" + QString::number(code & 0xFF, 16);
    }
    else if ((code & 0xFFF0) == 0x0080) // ADD
    {
        instruction = "ADD R" + QString::number(code & 0xF, 16);
    }
    else if ((code & 0xFFF0) == 0x0090) // SUB
    {
        instruction = "SUB R" + QString::number(code & 0xF, 16);
    }
    else if ((code & 0xFFF0) == 0x00A0) // LD
    {
        instruction = "LD R" + QString::number(code & 0xF, 16);
    }
    else if ((code & 0xFFF0) == 0x00B0) // XCH
    {
        instruction = "XCH R" + QString::number(code & 0xF, 16);
    }
    else if ((code & 0xFFF0)== 0x00C0) // BBL
    {
        instruction = "BBL 0x" + QString::number(code & 0xF, 16);
    }
    else if ((code & 0xFFF0) == 0x00D0) // LDM
    {
        instruction = "LDM 0x" + QString::number(code & 0xF, 16);
    }
    else if ((code & 0xFFFF) == 0x00E0) // WRM
    {
        instruction = "WRM";
    }
    else if ((code & 0xFFFF) == 0x00E1) // WMP
    {
        instruction = "WMP";
    }
    else if ((code & 0xFFFF) == 0x00E2) // WRR
    {
        instruction = "WRR";
    }
    else if ((code & 0xFFFF) == 0x00E3) // WPM
    {
        instruction = "WPM";
    }
    else if ((code & 0xFFFF) == 0x00E4) // WR0
    {
        instruction = "WR0";
    }
    else if ((code & 0xFFFF) == 0x00E5) // WR1
    {
        instruction = "WR1";
    }
    else if ((code & 0xFFFF) == 0x00E6) // WR2
    {
        instruction = "WR2";
    }
    else if ((code & 0xFFFF) == 0x00E7) // WR3
    {
        instruction = "WR3";
    }
    else if ((code & 0xFFFF) == 0x00E8) // SBM
    {
        instruction = "SBM";
    }
    else if ((code & 0xFFFF) == 0x00E9) // RDM
    {
        instruction = "RDM";
    }
    else if ((code & 0xFFFF) == 0x00EA) // RDR
    {
        instruction = "RDR";
    }
    else if ((code & 0xFFFF) == 0x00EB) // ADM
    {
        instruction = "ADM";
    }
    else if ((code & 0xFFFF) == 0x00EC) // RD0
    {
        instruction = "RD0";
    }
    else if ((code & 0xFFFF) == 0x00ED) // RD1
    {
        instruction = "RD1";
    }
    else if ((code & 0xFFFF) == 0x00EE) // RD2
    {
        instruction = "RD2";
    }
    else if ((code & 0xFFFF) == 0x00EF) // RD3
    {
        instruction = "RD3";
    }
    else if ((code & 0xFFFF) == 0x00F0) // CLB
    {
        instruction = "CLB";
    }
    else if ((code & 0xFFFF) == 0x00F1) // CLC
    {
        instruction = "CLC";
    }
    else if ((code & 0xFFFF) == 0x00F2) // IAC
    {
        instruction = "IAC";
    }
    else if ((code & 0xFFFF) == 0x00F3) // CMC
    {
        instruction = "CMC";
    }
    else if ((code & 0xFFFF) == 0x00F4) // CMA
    {
        instruction = "CMA";
    }
    else if ((code & 0xFFFF) == 0x00F5) // RAL
    {
        instruction = "RAL";
    }
    else if ((code & 0xFFFF) == 0x00F6) // RAR
    {
        instruction = "RAR";
    }
    else if ((code & 0xFFFF) == 0x00F7) // TCC
    {
        instruction = "TCC";
    }
    else if ((code & 0xFFFF) == 0x00F8) // DAC
    {
        instruction = "DAC";
    }
    else if ((code & 0xFFFF) == 0x00F9) // TCS
    {
        instruction = "TCS";
    }
    else if ((code & 0xFFFF) == 0x00FA) // STC
    {
        instruction = "STC";
    }
    else if ((code & 0xFFFF) == 0x00FB) // DAA
    {
        instruction = "DAA";
    }
    else if ((code & 0xFFFF) == 0x00FC) // KBP
    {
        instruction = "KBP";
    }
    else if ((code & 0xFFFF) == 0x00FD) // DCL
    {
        instruction = "DCL";
    }

    return instruction;
}

QString Debugger::commandToString(unsigned code)
{
    QString result;

    unsigned hiByte = (code & 0xFF00) >> 8;
    unsigned lowByte = code & 0x00FF;

    if (hiByte != 0)
    {
        result = QString("%1 %2").arg(QString::number(hiByte, 16), QString::number(lowByte, 16));
    }
    else
    {
        result = QString::number(lowByte, 16);
    }

    return result;
}

QString Debugger::addressToString(unsigned addr)
{
    QString result;

    if (addr < 0x10)
    {
        result = QString("00").append(QString::number(addr, 16));
    }
    else if (addr < 0x100)
    {
        result = QString("0").append(QString::number(addr, 16));
    }
    else
    {
        result = QString::number(addr, 16);
    }

    return result;
}

void Debugger::addBreakpoint(unsigned addr)
{
    breakpointAddresses.insert(addr);
}

void Debugger::removeBreakpoint(unsigned addr)
{
    breakpointAddresses.erase(addr);
}

void Debugger::clearBreakpoint()
{
    breakpointAddresses.clear();
}

bool Debugger::isBreakpoint(unsigned addr)
{
    auto it = breakpointAddresses.find(addr);
    return it != breakpointAddresses.end();
}


