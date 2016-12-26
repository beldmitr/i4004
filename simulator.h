#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <iostream>
#include <string>
#include <memory>

#include "GUI/delegategui.h"

#include "rom.h"
#include "pram.h"
#include "dram.h"
#include "cpu.h"



/*
 * The additional information for Simulator of Intel4004 is at
 * http://bitsavers.trailing-edge.com/pdf/intel/MCS4/MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf
 */
class Simulator
{
private:
    std::shared_ptr<DelegateGUI> delegate;

    std::shared_ptr<ROM> rom;
    std::shared_ptr<PRAM> pram;
    std::shared_ptr<DRAM> dram;
    std::shared_ptr<CPU> cpu;

    // methods
    void evalCommand(int);

    void NOP();
    void JCN(unsigned int condition, unsigned int address);
    void FIM(unsigned int pair, unsigned int data);
    void SRC(unsigned int pair);
    void FIN(unsigned int pair);
    void JIN(unsigned int pair);
    void JUN(unsigned int address1, unsigned int address2);
    void JMS(unsigned int address1, unsigned int address2);
    void INC(unsigned int reg);
    void ISZ(unsigned int reg, unsigned int address);
    void ADD(unsigned int reg);
    void SUB(unsigned int reg);
    void LD(unsigned int reg);
    void XCH(unsigned int reg);
    void BBL(unsigned int data);
    void LDM(unsigned int data);
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
    Simulator(std::shared_ptr<DelegateGUI> delegate);

    void setCode(std::vector<unsigned int> compiledCode);
    void step();

};

#endif // SIMULATOR_H
