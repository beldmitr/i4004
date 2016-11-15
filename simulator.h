#ifndef SIMULATOR_H
#define SIMULATOR_H



#include "rom.h"
#include "pram.h"
#include "dram.h"
#include "cpu.h"

#include <string>

class Simulator
{
//private:
public:
    ROM* rom;
    PRAM* pram;
    DRAM* dram;
    CPU* cpu;

    // methods
    void evalCommand(int);

    void NOP();
    void JCN(int condition, int address);
    void FIM(int pair, int data);
    void SRC(int pair);
    void FIN(int pair);
    void JIN(int pair);
    void JUN(int address1, int address2);
    void JMS(int address1, int address2);
    void INC(int reg);
    void ISZ(int reg, int address);
    void ADD(int reg);
    void SUB(int reg);
    void LD(int reg);
    void XCH(int reg);
    void BBL(int data);
    void LDM(int data);
    void WRM();
    void WMP();
    void WRR();
    void WR0();
    void WR1();
    void WR2();
    void WR3();
    void SBM();
    void RDM();
    void RDR();
    void ADM();
    void RD0();
    void RD1();
    void RD2();
    void RD3();
    void CLB();
    void CLC();
    void IAC();
    void CMC();
    void CMA();
    void RAL();
    void RAR();
    void TCC();
    void DAC();
    void TCS();
    void STC();
    void DAA();
    void KBP();
    void DCL();

public:
    Simulator();

    void step();

};

#endif // SIMULATOR_H
