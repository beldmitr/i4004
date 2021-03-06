#include "simulator.h"

Simulator::Simulator(Compiler& compiler) : QObject(),
    rom(new ROM(16)), dram(new DRAM(8)), cpu(new CPU)
{
    this->compiler = &compiler;

    /*************************************
     *  Connects
     *************************************/

    // Compiler
    connect(this->compiler, &Compiler::onCompiled, [=](){
        std::vector<unsigned int> code = this->compiler->getObjectCode();
        this->setCode(code);
    });
}

Simulator::~Simulator()
{
    // delete or finalize here something
}

void Simulator::setDelay(unsigned int delay)
{
    this->delay = delay;
}

void Simulator::setCode(std::vector<unsigned int> compiledCode)
{
    rom->flashRom(compiledCode);
}

void Simulator::step()
{
    unsigned int code = rom->getValue(cpu->getPC());

    bool isLongCommand = Debugger::hasNextByte(code);

    if (isLongCommand)
    {
        int low = rom->getValue(cpu->getPC() + 1);  // read the next byte
        code = (code << 8) | low;   // combine code to 2 byte
    }

    try
    {
        evalCommand(code);
        lastError = "";
    }
    catch (const LogExceptions& ex)
    {
        lastError = QString(ex.what());
    }

    if (!lastError.isEmpty())
    {
        emit onEvalCommand(lastError);
    }

    if (!isPlaying || delay >= threshold)
    {
        emit onStopPlaying();
    }
}

void Simulator::play()
{
    if (!isPlaying)
    {
        isPlaying = true;
        QtConcurrent::run([=]()
        {
            while(isPlaying)
            {
                emit onStartPlaying();
                int pc = this->cpu->getPC();
                bool isBreakpoint = Debugger::isBreakpoint(pc);
                if (isBreakpoint && !isStopped)
                {
                    this->stop();
                    isStopped = true;
                    return;
                }
                isStopped = false;
                step();
                QThread::msleep(delay);
            }
        });
    }
}

void Simulator::stop()
{
    isPlaying = false;
    emit onStopPlaying();
}

void Simulator::reset()
{
    cpu->reset();
    rom->reset();
    dram->reset();

    if (!isPlaying || delay >= threshold)
    {
        emit onStopPlaying();
    }
}

std::shared_ptr<CPU> Simulator::getCpu() const
{
    return cpu;
}

std::shared_ptr<DRAM> Simulator::getDram() const
{
    return dram;
}

std::shared_ptr<ROM> Simulator::getRom() const
{
    return rom;
}

bool Simulator::getIsPlaying() const
{
    return isPlaying;
}

void Simulator::evalCommand(int command)
{
    if ((command & 0xFFFF) == 0x0000) // NOP
    {
        NOP();
    }
    else if ((command & 0xF000) == 0x1000) // JCN
    {
        JCN((command & 0x0F00) >> 8, command & 0x00FF);
    }
    else if ((command & 0xF100) == 0x2000) // FIM
    {
        FIM((command & 0xE00) >> 9, command & 0xFF);
    }
    else if ((command & 0xFFF1) == 0x0021) // SRC
    {
        SRC((command & 0x0E) >> 1);
    }
    else if ((command & 0xFFF1) == 0x0030) // FIN
    {
        FIN((command & 0xE) >> 1);
    }
    else if ((command & 0xFFF1) == 0x0031) // JIN
    {
        JIN((command & 0xE) >> 1);
    }
    else if ((command & 0xF000) == 0x4000) // JUN
    {
        JUN((command & 0x0F00) >> 8, command & 0x00FF);
    }
    else if ((command & 0xF000) == 0x5000) // JMS
    {
        JMS((command & 0x0F00) >> 8, command & 0x00FF);
    }
    else if ((command & 0xFFF0) == 0x0060) // INC
    {
        INC(command & 0xF);
    }
    else if ((command & 0xF000) == 0x7000) // ISZ
    {
        ISZ((command & 0x0F00) >> 8, command & 0xFF);
    }
    else if ((command & 0xFFF0) == 0x0080) // ADD
    {
        ADD(command & 0xF);
    }
    else if ((command & 0xFFF0) == 0x0090) // SUB
    {
        SUB(command & 0xF);
    }
    else if ((command & 0xFFF0) == 0x00A0) // LD
    {
        LD(command & 0xF);
    }
    else if ((command & 0xFFF0) == 0x00B0) // XCH
    {
        XCH(command & 0xF);
    }
    else if ((command & 0xFFF0)== 0x00C0) // BBL
    {
        BBL(command & 0xF);
    }
    else if ((command & 0xFFF0) == 0x00D0) // LDM
    {
        LDM(command & 0xF);
    }
    else if ((command & 0xFFFF) == 0x00E0) // WRM
    {
        WRM();
    }
    else if ((command & 0xFFFF) == 0x00E1) // WMP
    {
        WMP();
    }
    else if ((command & 0xFFFF) == 0x00E2) // WRR
    {
        WRR();
    }
    else if ((command & 0xFFFF) == 0x00E4) // WR0
    {
        WR0();
    }
    else if ((command & 0xFFFF) == 0x00E5) // WR1
    {
        WR1();
    }
    else if ((command & 0xFFFF) == 0x00E6) // WR2
    {
        WR2();
    }
    else if ((command & 0xFFFF) == 0x00E7) // WR3
    {
        WR3();
    }
    else if ((command & 0xFFFF) == 0x00E8) // SBM
    {
        SBM();
    }
    else if ((command & 0xFFFF) == 0x00E9) // RDM
    {
        RDM();
    }
    else if ((command & 0xFFFF) == 0x00EA) // RDR
    {
        RDR();
    }
    else if ((command & 0xFFFF) == 0x00EB) // ADM
    {
        ADM();
    }
    else if ((command & 0xFFFF) == 0x00EC) // RD0
    {
        RD0();
    }
    else if ((command & 0xFFFF) == 0x00ED) // RD1
    {
        RD1();
    }
    else if ((command & 0xFFFF) == 0x00EE) // RD2
    {
        RD2();
    }
    else if ((command & 0xFFFF) == 0x00EF) // RD3
    {
        RD3();
    }
    else if ((command & 0xFFFF) == 0x00F0) // CLB
    {
        CLB();
    }
    else if ((command & 0xFFFF) == 0x00F1) // CLC
    {
        CLC();
    }
    else if ((command & 0xFFFF) == 0x00F2) // IAC
    {
        IAC();
    }
    else if ((command & 0xFFFF) == 0x00F3) // CMC
    {
        CMC();
    }
    else if ((command & 0xFFFF) == 0x00F4) // CMA
    {
        CMA();
    }
    else if ((command & 0xFFFF) == 0x00F5) // RAL
    {
        RAL();
    }
    else if ((command & 0xFFFF) == 0x00F6) // RAR
    {
        RAR();
    }
    else if ((command & 0xFFFF) == 0x00F7) // TCC
    {
        TCC();
    }
    else if ((command & 0xFFFF) == 0x00F8) // DAC
    {
        DAC();
    }
    else if ((command & 0xFFFF) == 0x00F9) // TCS
    {
        TCS();
    }
    else if ((command & 0xFFFF) == 0x00FA) // STC
    {
        STC();
    }
    else if ((command & 0xFFFF) == 0x00FB) // DAA
    {
        DAA();
    }
    else if ((command & 0xFFFF) == 0x00FC) // KBP
    {
        KBP();
    }
    else if ((command & 0xFFFF) == 0x00FD) // DCL
    {
        DCL();
    }
    else
    {
        unsigned addr = cpu->getPC();
        NOP();

        std::cerr << "Simulator: evalCommand : Unknown command 0x" << std::hex << command << " at address 0x" << addr << std::endl;

        throw LogExceptions("Simulator", "Command 0x" + QString::number(command, 16).toStdString() + " at address 0x"
                            + QString::number(addr, 16).toStdString() + " can't be evaluated");
    }
}

/**
 * @brief Simulator::NOP - NO OPERATION
 */
void Simulator::NOP()
{
    /*
     * NO OPERATION
     *
     * This instruction occupies one byte.
     *
     * No operation is performed. The program counter is incremented by one and execution
     * continues with the next sequential instruction.
     *
     * The carry bit is not affected.
     */
    cpu->setPC(cpu->getPC() + 1);
    cpu->setCycles(cpu->getCycles() + 1);
}

/**
 * @brief Simulator::JCN - JUMP ON CONDITION
 * @param condition - (4 bit) jumps if condition is true
 * @param address - (8 bit) address to jump
 */
void Simulator::JCN(unsigned int condition, unsigned int address)
{
    /*
     * JUMP ON CONDITION
     *
     * The JCN instruction occupies two bytes.
     *
     * If the condition specified by condition(CN) is false, no action occurs and program execution
     * continues with the next sequential instruction. If the condition specified by
     * CN is true, the 8 bits specified by address (ADDR) replace the lower 8 bits of the program
     * counter. The highest 4 bits of the program counter are unchanged. Therefore,
     * program execution continues at the specified address on the same page of memory
     * in which the JCN instruction is located. The carry bit is not affected.
     *
     * The condition code is specified in the assembly language statement as a decimal
     * value from 0 to 15, which is represented in the assembled instruction as the
     * corresponding 4 bit hexadecimal digit. Each bit of the condition code has a
     * meaning, as follows:
     *
     *        CN
     *  _______________
     * |C1_|C2_|C3_|C4_|
     *   |   |   |   |
     *   |   |   |   If this bit = 1, jump if the test signal of the 4004 is = 0.
     *   |   |   |
     *   |   |   If this bit = 1, jump if the carry bit = 1
     *   |   |
     *   |   If this bit = 1, jump if the accumulator = 0
     *   |
     *   If this bit = 1, invert the other jump conditions.
     *
     * In Boolean notation I the equation for the jump condition is as follows:
     * JUMP = !C1 * ((ACC == 0) * C2 + (carry == 1) * C3 + !TEST * C4) +
     *         C1 * (((ACC != 0) + !C2) * ((carry == 0) + !C3) * (TEST + !C4))
     *
     *
     * Note: If the JCN instruction is located in the last two locations of a page in
     * memory and the jump condition is true, the highest 4 bits of the program counter
     * are incremented by 1, causing control to be transferred to the corresponding location
     * on the next page.
     */

    if (condition > 0xF)
    {
        std::cerr << std::hex << "Error: JCN condition. 0x" << condition
                  << " is invalid, because is bigger than 4 bit." << std::endl;
        return;
    }

    if (address > 0xFF)
    {
        std::cerr << std::hex << "Error: 0x" << address << " is too big. It may be 8 bit." << std::endl;
        return;
    }

    bool c4 = (condition & 0x1) == 1;
    bool c3 = ((condition & 0x2) >> 1) == 1;
    bool c2 = ((condition & 0x4) >> 2) == 1;
    bool c1 = ((condition & 0x8) >> 3) == 1;

    bool isJump = (!c1 & (((cpu->getAcc() == 0) & c2) | ((cpu->getCarry() == 1) & c3) | ((cpu->getTest() == 0) & c4))) |
            (c1 & (((cpu->getAcc() != 0) | !c2) & ((cpu->getCarry() == 0) | !c3) & ((cpu->getTest() == 1) | !c4)));

    if (isJump)
    {
        /*
         * If the condition is true, the 8 bits specified by
         * address replace the lower 8 bits of the program counter.
         * The highest 4 bits of the program counter are unchanged.
         */

        if ((cpu->getPC() & 0xFF) == 0xFE)
        {
            // See note
            // It must jump to the next page

            unsigned actualPage = (cpu->getPC() & 0x0F00) >> 8;

            cpu->setPC((actualPage + 1) << 8 | (address & 0xFF));
        }
        else
        {
            cpu->setPC((cpu->getPC() & 0x0F00) | (address & 0xFF));
        }
    }
    else
    {
        /*
         * If the condition specified is false, no action occurs and program execution
         * continues with the next sequential instruction.
         */
        cpu->setPC(cpu->getPC() + 2);
    }

    cpu->setCycles(cpu->getCycles() + 2);
}

/**
 * @brief Simulator::FIM - FETCH IMMEDIATE
 * @param pair - pair [0-7]
 * @param data - data (8 bit)
 */
void Simulator::FIM(unsigned int pair, unsigned int data)
{
    /*
     * FETCH IMMEDIATE
     *
     * The FIM instruction occupies two bytes.
     *
     * 0010xxx0yyyyyyyy
     *
     * xxx - register pair (RP) (0b000 - 0b111)
     * yyyyyyyy - data (8 bit)
     *
     * The 8 bits of immediate data are loaded into the register pair specified by RP.
     * The carry bit is not affected.
     */

    if (pair > 0x7)
    {
        std::cerr << "Error: wrong number of pair " << pair << std::endl;
        return;
    }

    if (data > 0xFF)
    {
        std::cerr << std::hex << "Warning: 0x" << data
                  << " may consider only 8 bit. It will be reduced." << std::endl;
    }

    cpu->setPairs(pair, data & 0xFF);
    cpu->setPC(cpu->getPC() + 2);
    cpu->setCycles(cpu->getCycles() + 2);
}

/**
 * @brief Simulator::SRC - SEND REGISTER CONTROL
 * @param pair - pair [0-7]
 */
void Simulator::SRC(unsigned int pair)
{
    /*
    * SEND REGISTER CONTROL
    *
    * The SRC instruction occupies one byte.
    *
    * 0010xxx1
    * xxx - RP register pair [0x0 - 0x7]
    *
    * The 8 bits contained in the register pair specified by RP are used as an address.
    * This address may designate a particular DATA RAM data character, a DATA RAM
    * status character, a RAM output port, or a ROM input/output port.
    *
    * The carry bit and the contents of the register pair are unaffected.
    *
    * The 8 bits of the address sent by the SRC are interpreted as follows:
    * 1) When referencing a DATA RAM data character:
    *   xxyyzzzz
    *   xx   - 1 of 4 DATA RAM chips within the DATA RAM bank previously selected by a DCL instruction.
    *   yy   - 1 of 4 registers within the DATA RAM chip.
    *   zzzz - 1 of 16 4-bit data characters within the register
    *
    * 2) When referencing a DATA RAM status character:
    *   xxyyzzzz
    *   xx   - 1 of 4 DATA RAM chips within the DATA RAM bank previously selected by a DCL instruction.
    *   yy   - 1 of 4 registers within the DATA RAM chip.
    *   zzzz - These bits are not relevant for this reference.
    *
    * 3) When referencing a RAM output port:
    *   xxyyyyyy
    *   xx     - The port associated with 1 of 4 DATA RAM chips within the DATA RAM bank previously
    *            selected by a DCL.
    *   yyyyyy - These bits are not relevant for this reference.
    *
    * 4) When referencing a ROM input or output port:
    *   xxxxyyyy
    *   xxxx - The port associated with 1 of 16 ROM's.
    *   yyyy - These bits are not relevant for this reference.
    */

    if (pair > 0x7)
    {
        std::cerr << "Error: wrong number of pair " << pair << std::endl;
        return;
    }

    int pairValue = cpu->getPairAt(pair & 0x7);

    cpu->setSrc(pairValue);
    cpu->setPC(cpu->getPC() + 1);
    cpu->setCycles(cpu->getCycles() + 1);
}

/**
 * @brief Simulator::FIN - FETCH INDIRECT
 * @param pair - pair [0-7]
 */
void Simulator::FIN(unsigned int pair)
{
    /*
     * FETCH INDIRECT
     *
     * 0011xxx0
     * xxx - RP register pair (0b000 - 0b111)
     *
     * The contents of registers 0 and 1 are concatenated to form the lower 8 bits of a
     * ROM or program RAM address. The upper 4 bits of the address are assumed
     * equal to the upper 4 bits of the address at which the FIN instruction is located
     * (that is, the address of the FIN instruction and the address referenced by register
     * 0 and 1 are on the same page). The 8 bits at the designated address are loaded
     * into the register pair specified by RP. The 8 bits at the designated address are
     * unaffected; the contehts of registers 0 and I are unaffected unles s RP = 0.
     *
     * The carry bit is not affected.
     *
     * Note:
     * There is an exception: If a FIN instruction is located in the last location of a page,
     * the upper 4 bits of the designated address will be assumed equal to the upper 4 bits of the
     * next page.
     */

    if (pair > 0x7)
    {
        std::cerr << "Error: wrong number of pair " << pair << std::endl;
        return;
    }

    // high order program counter Field (4 bit)
    int pcHigh = cpu->getPC() & 0x0F00;

    /*
     * If a FIN instruction is located in the last location of a page,
     * the upper 4 bits of the designated address will be assumed equal to the upper 4 bits of the
     * next page.
     *
     * See note above
     */
    if ((cpu->getPC() & 0xFF) == 0xFF)
    {
        unsigned actualPage = pcHigh >> 8;
        actualPage += 1;
        pcHigh = (actualPage << 8) % 0x1000;
    }
    int addr = pcHigh | (cpu->getRegisterAt(pair * 2) << 4) | cpu->getRegisterAt((pair * 2) + 1); // do with getPairAt ???

    int value = rom->getValue(addr);
    cpu->setPairs(pair & 0b111, value);

    cpu->setPC(cpu->getPC() + 1);
    cpu->setCycles(cpu->getCycles() + 1);
}

/**
 * @brief Simulator::JIN - JUMP INDIRECT
 * @param pair - pair [0-7]
 */
void Simulator::JIN(unsigned int pair)
{
    /*
     * JUMP INDIRECT
     *
     * The JIN instruction occupies one byte.
     *
     * 0011xxx1
     * xxx - RP register pair (0b000 - 0b111)
     *
     * The 8 bits held in the register pair specified by RP are loaded into the lower 8
     * bits of the program counter. The highest 4 bits of the program counter are unchanged.
     * Therefore, program execution continues at this address on the same
     * page of memory in which the JIN instruction is loaded.
     *
     * The carry bit is not affected.
     *
     * Note: when JIN is located at the address
     * (PH) 1111 1111 program control is transferred to the next page in sequence and
     * not to the same page where the JIN instruction is located.
     * That is, the next address is (PH+1) (RRR0) (RRR1) and not (PH) (RRR0) (RRR1)
     */

    if (pair > 0x7)
    {
        std::cerr << "Error: wrong number of pair " << pair << std::endl;
        return;
    }

    unsigned actualPage = (cpu->getPC() & 0x0F00) >> 8;

    if ((cpu->getPC() & 0xFF) == 0xFF)
    {
        actualPage += 1;
        int addr = (actualPage << 8) | cpu->getPairAt(pair & 0x7);
        cpu->setPC(addr);
    }
    else
    {
        int addr = (cpu->getPC() & 0x0F00) | cpu->getPairAt(pair & 0x7);
        cpu->setPC(addr);
    }


    cpu->setCycles(cpu->getCycles() + 1);
}

/**
 * @brief Simulator::JUN - JUMP UNCONDITIONALLY
 * @param address1 - high address (4 bit)
 * @param address2 - low address (8 bit)
 */
void Simulator::JUN(unsigned int address1, unsigned int address2)
{
    /*
     * JUMP UNCONDITIONALLY
     *
     * The JUN instruction occupies two bytes/
     *
     * 0100 xxxx xxxx xxxx
     *
     * xxxx xxxx xxxx - address (ADDR)
     *
     * Program execution is transferred to the instruction at location ADDR, which may
     * be anywhere in memory. (If the rUN is located in ROM, ADDR is a ROM address;
     * if located in program RAM, ADDR is a program RAM address).
     *
     * The carry bit is not affected.
     */

    if (address1 > 0xF)
    {
        std::cerr << std::hex << "Warning: address1 0x" << address1
                  << " may consider 4 bit. It will be reduced." << std::endl;
    }

    if (address2 > 0xFF)
    {
        std::cerr << std::hex << "Warning: address2 0x" << address2
                  << " may consider 8 bit. It will be reduced." << std::endl;
    }

    cpu->setPC(((address1 & 0xF) << 8) | (address2 & 0xFF));

    cpu->setCycles(cpu->getCycles() + 2);
}

/**
 * @brief Simulator::JMS - Jump to subroutine
 * @param address1 - high address (4 bit)
 * @param address2 - low address (8 bit)
 */
void Simulator::JMS(unsigned int address1, unsigned int address2)
{
    /*
     * JUMP TO SUBROUTINE
     *
     * The JMS instruction occupies two bytes.
     *
     * 0101 xxxx xxxx xxxx
     * xxxx xxxx xxxx - address (ADDR)
     *
     * The address of the instruction immediately following the JMS is written to the
     * address stack for later use by a BBL instruction. Program execution continues at
     * memory address ADDR, which may be on any page.
     *
     * The carty bit is not affected.
     */

    if (address1 > 0xF)
    {
        std::cerr << std::hex << "Warning: address1 0x" << address1
                  << " may consider 4 bit. It will be reduced." << std::endl;
    }

    if (address2 > 0xFF)
    {
        std::cerr << std::hex << "Warning: address2 0x" << address2
                  << " may consider 8 bit. It will be reduced." << std::endl;
    }

    cpu->getStack()->write(cpu->getPC() + 2);
    cpu->setPC(((address1 & 0xF) << 8) | (address2 & 0xFF));
    cpu->setCycles(cpu->getCycles() + 2);
}

/**
 * @brief Simulator::INC - INCREMENT REGISTER
 * @param reg - register [0-15]
 */
void Simulator::INC(unsigned int reg)
{
    /*
     * INCREMENT REGISTER
     * 0110 xxxx
     * xxxx - register (REG) (0x0 - 0xF)
     *
     * The index register indicated by REG is incremented by one.
     *
     * The carry bit is not affected.
     */

    if (reg > 0xF)
    {
        std::cerr << "Error: wrong number of register " << reg << std::endl;
        return;
    }

    int value = (cpu->getRegisterAt(reg) + 1) % 0x10;
    cpu->setRegisters(reg & 0xF, value);

    cpu->setPC(cpu->getPC() + 1);
    cpu->setCycles(cpu->getCycles() + 1);
}

/**
 * @brief Simulator::ISZ - INCREMENT AND SKIP IF ZERO
 * @param reg - register [0-15]
 * @param address - address for jumpng (8 bit)
 */
void Simulator::ISZ(unsigned int reg, unsigned int address)
{
    /*
     * INCREMENT AND SKIP IF ZERO
     *
     * The ISZ instruction occupies two bytes.
     *
     * 0111 xxxx yyyy yyyy
     * xxxx - register (REG) (0x0 - 0xF)
     * yyyy yyyy - address (ADDR) (8 bit)
     *
     * The index register specified by REG is incremented by one. If the result is 0000 B,
     * program execution continues with the next sequential instruction. If the result
     * does not equal 0000 B, the 8 bits specified by ADDR replace the lowest 8 bits of
     * the program counter. The highest 4 bits of the program counter are unchanged.
     * Therefore I program execution continues at the specified address on the same page
     * of memory in which the ISZ instruction is located.
     *
     * The carry bit is not affected.
     *
     * Note: If the ISZ instruction is located in the last two locations of a page in
     * memory and the incrementation produces a non-zero result, the highest 4 bits of
     * the program counter are incremented by 1, causing control to be transferred to the
     * corresponding location on the next page.
     */

    if (reg > 0xF)
    {
        std::cerr << "Error: wrong number of register " << reg << std::endl;
        return;
    }

    if (address > 0xFF)
    {
        std::cerr << std::hex << "Warning: address 0x" << address
                  << " may consider only 8 bit. It will be reduced." << std::endl;
    }

    int value = (cpu->getRegisterAt(reg) + 1) % 0x10;
    cpu->setRegisters(reg & 0xF, value);

    // check the condition
    if (cpu->getRegisterAt(reg) == 0)
    {
        cpu->setPC(cpu->getPC() + 2);
    }
    else
    {
        cpu->setPC((cpu->getPC() & 0x0F00) | (address & 0xFF));
    }

    cpu->setCycles(cpu->getCycles() + 2);
}

/**
 * @brief Simulator::ADD - ADD REGISTER TO ACCUMULATOR WITH CARRY
 * @param reg - register [0-15]
 */
void Simulator::ADD(unsigned int reg)
{
    /*
     * ADD REGISTER TO ACCUMULATOR WITH CARRY
     *
     * 1000 xxxx
     * xxxx - register (REG)
     *
     * The contents of the index register REG plus the contents of the carry bit are
     * added to the accumulator. The result is kept in the accumulator; the contents
     * of REG are unchanged. The carry bit is set if there is, a carry out of the highorder
     * bit position, and reset if there is no carty.
     */

    if (reg > 0xF)
    {
        std::cerr << "Error: wrong number of register " << reg << std::endl;
        return;
    }

    int value = cpu->getRegisterAt(reg) + cpu->getAcc() + cpu->getCarry();

    cpu->setCarry((value & 0x10) >> 4);
    cpu->setAcc(value % 0x10);

    cpu->setPC(cpu->getPC() + 1);
    cpu->setCycles(cpu->getCycles() + 1);
}

/**
 * @brief Simulator::SUB - SUBTRACT REGISTER FROM ACCUMULATOR WITH BORROW
 * @param reg - register [0-15]
 */
void Simulator::SUB(unsigned int reg)
{
    /*
     * SUBTRACT REGISTER FROM ACCUMULATOR WITH BORROW
     *
     * 1001 xxxx
     * xxxx - register (REG)
     *
     * The contents of index register REG are subtracted with borrow from the accumulator.
     * The result is kept in the accumulator; the contents of REG are unchanged. A borrow
     * from the previous subtraction is indicated by the carry bit being equal to one ·at
     * the beginning of this instruction. If the carry bit equals zero at the beginning of
     * this instruction it is assumed that no borrow occurred from the previous subtraction.
     *
     * This instruction sets the carry bit if there is no borrow out of the high order bit
     * position, and resets the carry bit if there is a borrow.
     *
     * The subtract with borrow operation is actually performed by complementing each bit
     * of the contents of REG and adding the resulting value plus the complement of the
     * carry bit to the accumulator.
     */

    if (reg > 0xF)
    {
        std::cerr << "Error: wrong number of register " << reg << std::endl;
        return;
    }

    int complementCarry = cpu->getCarry() == 0 ? 1 : 0;
    int complementReg = (~cpu->getRegisterAt(reg)) & 0xF;
    int value = cpu->getAcc() + complementReg + complementCarry;

    int borrow = (value & 0x10) >> 4;

    cpu->setCarry(borrow);

    cpu->setAcc(value % 0x10);

    cpu->setPC(cpu->getPC() + 1);
    cpu->setCycles(cpu->getCycles() + 1);
}

/**
 * @brief Simulator::LD - LOAD ACCUMULATOR
 * @param reg - register [0-15]
 */
void Simulator::LD(unsigned int reg)
{
    /*
     * LOAD ACCUMULATOR
     *
     * 1010 xxxx
     * xxxx - register (REG)
     *
     * The contents of REG are stored into the accumulator, replacing the previous contents
     * of the accumulator. The contents of REG are unchanged. The carry bit is not affected.
     */

    if (reg > 0xF)
    {
        std::cerr << "Error: wrong number of register " << reg << std::endl;
        return;
    }

    cpu->setAcc(cpu->getRegisterAt(reg));

    cpu->setPC(cpu->getPC() + 1);
    cpu->setCycles(cpu->getCycles() + 1);
}

/**
 * @brief Simulator::XCH - EXCHANGE REGISTER AND ACCUMULATOR
 * @param reg - register [0-15]
 */
void Simulator::XCH(unsigned int reg)
{
    /*
     * EXCHANGE REGISTER AND ACCUMULATOR
     *
     * 1011 xxxx
     * xxxx - register (REG)
     *
     * The contents of the register specified by REG are exchanged with the contents of
     * the accumulator.
     *
     * The carry bit is not affected.
     */

    if (reg > 0xF)
    {
        std::cerr << "Error: wrong number of register " << reg << std::endl;
        return;
    }

    int r = cpu->getRegisterAt(reg);
    int a = cpu->getAcc();

    cpu->setRegisters(reg, a);
    cpu->setAcc(r);

    cpu->setPC(cpu->getPC() + 1);
    cpu->setCycles(cpu->getCycles() + 1);
}

/**
 * @brief Simulator::BBL - BRANCH BACK AND LOAD
 * @param data - data (4 bit)
 */
void Simulator::BBL(unsigned int data)
{
    /*
     * BRANCH BACK AND LOAD
     *
     * The BBL instruction occupies one byte.
     *
     * 1100 xxxx
     * xxxx - data
     *
     * The 4 bits of immediate data encoded in the instruction are loaded into the accumulator.
     * Then the last 12 bit address saved on the address stack (by a JMS instruction)
     * is read from the stack and placed in the program counter. Thus, execution continues
     * with the instruction immediately following the last JMS instruction.
     *
     * The carry bit is not affected.
     */

    if (data > 0xF)
    {
        std::cerr << std::hex << "Warning: data " << data
                  << " is too big and will be reduced to 4 bits." << std::endl;
    }

    cpu->setAcc(data);

    int stackedAddress = cpu->getStack()->read();
    cpu->setPC(stackedAddress);

    cpu->setCycles(cpu->getCycles() + 1);
}

/**
 * @brief Simulator::LDM - LOAD ACCUMULATOR IMMEDIATE
 * @param data - data (4 bit)
 */
void Simulator::LDM(unsigned int data)
{
    /*
     * LOAD ACCUMULATOR IMMEDIATE
     *
     * The LDM instruction occupies one byte.
     *
     * 1101 xxxx
     * xxxx - data
     *
     * The 4 bits of immediate data are loaded into the accumulator.
     *
     * The carry bit is not affected.
     */

    if (data > 0xF)
    {
        std::cerr << std::hex << "Warning: data 0x" << data
                  << " is too big and will be reduced to 4 bits." << std::endl;
    }

    cpu->setAcc(data & 0xF);

    cpu->setPC(cpu->getPC() + 1);
    cpu->setCycles(cpu->getCycles() + 1);
}

/**
 * @brief Simulator::WRM - WRITE DATA RAM CHARACTER
 */
void Simulator::WRM()
{
    /*
     * WRITE DATA RAM CHARACTER
     *
     * 1110 0000
     *
     * The contents of the accumulator are written into the DATA RAM data
     * character specified by the last SRC instruction.
     *
     * The carry bit and the accumulator are not affected.
     */

    /*
     * The 8 bits of the address sent by the SRC are interpreted as follows:
     *
     * When referencing a DATA RAM data character:
     *   xxyyzzzz
     *   xx   - 1 of 4 DATA RAM chips within the DATA RAM bank previously selected by a DCL instruction.
     *   yy   - 1 of 4 registers within the DATA RAM chip.
     *   zzzz - 1 of 16 4-bit data characters within the register
     *
     */
    int src = cpu->getSrc();

    int bank = cpu->getDcl();
    int chip = (src & 0b11000000) >> 6;
    int reg = (src & 0b00110000) >> 4;
    int character = src & 0xF;

    DataRAMBank* dataRAMBank = dram->getDataRAMBank(bank).get();
    DataRAMChip* dataRAMChip = dataRAMBank->getDataRAMChip(chip).get();
    DataRAMRegister* dataRAMRegister = dataRAMChip->getDataRAMRegister(reg).get();

    dataRAMRegister->setCharacter(character, cpu->getAcc());

    cpu->setPC(cpu->getPC() + 1);
    cpu->setCycles(cpu->getCycles() + 1);
}

/**
 * @brief Simulator::WMP - WRITE RAM PORT
 */
void Simulator::WMP()
{
    /*
     * WRITE RAM PORT
     *
     * 1110 0001
     *
     * The contents of the accumulator are written to the output port associated with the
     * DATA RAM chip selected by the last SRC instruction. This value will stay at the
     * output port until overwritten.
     *
     * The carry bit and the accumulator are unchanged.
     */

    /*
     * The 8 bits of the address sent by the SRC are interpreted as follows:
     *
     * When referencing a RAM output port:
     *   xxyyyyyy
     *   xx     - The port associated with 1 of 4 DATA RAM chips within the DATA RAM bank previously
     *            selected by a DCL.
     *   yyyyyy - These bits are not relevant for this reference.
     */


    int bank = cpu->getDcl();
    int chip = (cpu->getSrc() & 0b11000000) >> 6;

    dram->getDataRAMBank(bank)->getDataRAMChip(chip)->setOutput(cpu->getAcc());

    cpu->setPC(cpu->getPC() + 1);
    cpu->setCycles(cpu->getCycles() + 1);
}

/**
 * @brief Simulator::WRR - WRITE ROM PORT
 */
void Simulator::WRR()
{
    /*
     * WRITE ROM PORT
     *
     * 1110 0010
     *
     * The contents of the accumulator are written to the output port associated with the
     * ROM selected by the last SRC instruction. This value will stay at the output port
     * until overwritten.
     *
     * The carry bit and the accumulator are unchanged.
     */

    int romPage = (cpu->getSrc() & 0xFF) >> 4;
    rom->setIO(romPage, cpu->getAcc());

    cpu->setPC(cpu->getPC() + 1);
    cpu->setCycles(cpu->getCycles() + 1);
}

/**
 * @brief Simulator::WR0 - WRITE DATA RAM STATUS CHARACTER 0
 */
void Simulator::WR0()
{
    /*
     * Function is almost the same for WR0, WR1, WR2 and WR3
     */

    /*
     * WRITE DATA RAM STATUS CHARACTER
     *
     * 1110 01xx
     * xx - number [0-3] of the status character
     * For WR0 xx is 00, WR1 - 01, WR2 - 10, WR3 - 11
     *
     * The contents of the DATA RAM status character whose number from 0 to 3 is specified
     * by xx, associated with the DATA RAM register specified by tbe last SRC
     * instruction, are replaced by the contents of the accumulator.
     *
     * The carry bit and the accumulator are not affected.
     */

    /*
     * The 8 bits of the address sent by the SRC are interpreted as follows:
     *
     * When referencing a DATA RAM status character:
     *   xxyyzzzz
     *   xx   - 1 of 4 DATA RAM chips within the DATA RAM bank previously selected by a DCL instruction.
     *   yy   - 1 of 4 registers within the DATA RAM chip.
     *   zzzz - These bits are not relevant for this reference.
     */

    int chip = (cpu->getSrc() & 0b11000000) >> 6;
    int reg = (cpu->getSrc() & 0b00110000) >> 4;

    dram->getDataRAMBank(cpu->getDcl())->getDataRAMChip(chip)->
            getDataRAMRegister(reg)->setStatus(0, cpu->getAcc());

    cpu->setPC(cpu->getPC() + 1);
    cpu->setCycles(cpu->getCycles() + 1);
}

/**
 * @brief Simulator::WR1 - WRITE DATA RAM STATUS CHARACTER 1
 */
void Simulator::WR1()
{
    /*
     * Function is the almost same as the WR0 function. Look it for a description.
     */

    int chip = (cpu->getSrc() & 0b11000000) >> 6;
    int reg = (cpu->getSrc() & 0b00110000) >> 4;

    dram->getDataRAMBank(cpu->getDcl())->getDataRAMChip(chip)->
            getDataRAMRegister(reg)->setStatus(1, cpu->getAcc());

    cpu->setPC(cpu->getPC() + 1);
    cpu->setCycles(cpu->getCycles() + 1);
}

/**
 * @brief Simulator::WR2 - WRITE DATA RAM STATUS CHARACTER 2
 */
void Simulator::WR2()
{
    /*
     * Function is the almost same as the WR0 function. Look it for a description.
     */

    int chip = (cpu->getSrc() & 0b11000000) >> 6;
    int reg = (cpu->getSrc() & 0b00110000) >> 4;

    dram->getDataRAMBank(cpu->getDcl())->getDataRAMChip(chip)->
            getDataRAMRegister(reg)->setStatus(2, cpu->getAcc());

    cpu->setPC(cpu->getPC() + 1);
    cpu->setCycles(cpu->getCycles() + 1);
}

/**
 * @brief Simulator::WR3 - WRITE DATA RAM STATUS CHARACTER 3
 */
void Simulator::WR3()
{
    /*
     * Function is the almost same as the WR0 function. Look it for a description.
     */

    int chip = (cpu->getSrc() & 0b11000000) >> 6;
    int reg = (cpu->getSrc() & 0b00110000) >> 4;

    dram->getDataRAMBank(cpu->getDcl())->getDataRAMChip(chip)->
            getDataRAMRegister(reg)->setStatus(3, cpu->getAcc());

    cpu->setPC(cpu->getPC() + 1);
    cpu->setCycles(cpu->getCycles() + 1);
}

/**
 * @brief Simulator::SBM - SUBTRACT DATA RAM FROM MEMORY WITH BORROW
 */
void Simulator::SBM()
{
    /*
     * SUBTRACT DATA RAM FROM MEMORY WITH BORROW
     *
     * 1110 1000
     *
     * The value of the DATA RAM character specified by the last SRC instruction is subtracted
     * from the accumulator with borrow. The data character is unaffected. A borrow from the
     * previous subtraction is indicated by the carry bit being equal to one at the beginning
     * of this instruction. No borrow from the previous subtraction is indicated by the carry
     * bit being equal to zero at the beginning of this instruction.
     *
     * This instruction sets the carry bit if the result generates no borrow, and resets the
     * carry bit if the result generates a borrow.
     *
     * The subtract with borrow operation is actually performed by complementing each bit of
     * the data character and adding the resulting value plus the complement of the carry bit
     * to the accumulator.
     */

    /*
     * The 8 bits of the address sent by the SRC are interpreted as follows:
     *
     * When referencing a DATA RAM data character:
     *   xxyyzzzz
     *   xx   - 1 of 4 DATA RAM chips within the DATA RAM bank previously selected by a DCL instruction.
     *   yy   - 1 of 4 registers within the DATA RAM chip.
     *   zzzz - 1 of 16 4-bit data characters within the register
     */

    int bank = cpu->getDcl();
    int chip = (cpu->getSrc() & 0b11000000) >> 6;
    int reg = (cpu->getSrc() & 0b00110000) >> 4;
    int character = cpu->getSrc() & 0xF;

    int memValue = dram->getDataRAMBank(bank)->getDataRAMChip(chip)
            ->getDataRAMRegister(reg)->getCharacter(character);

    int result = cpu->getAcc() + (~memValue & 0xF) + !cpu->getCarry();
    cpu->setAcc(result & 0xF);
    cpu->setCarry((result & 0b10000) >> 4);

    cpu->setPC(cpu->getPC() + 1);
    cpu->setCycles(cpu->getCycles() + 1);
}

/**
 * @brief Simulator::RDM - READ DATA RAM DATA CHARACTER
 */
void Simulator::RDM()
{
    /*
     * READ DATA RAM DATA CHARACTER
     *
     * 1110 1001
     *
     * The DATA RAM data character specified by the last SRC instruction is loaded into
     * the accumulator. The carry bit and the data character are not affected.
     */

    /*
     * The 8 bits of the address sent by the SRC are interpreted as follows:
     *
     * When referencing a DATA RAM data character:
     *   xxyyzzzz
     *   xx   - 1 of 4 DATA RAM chips within the DATA RAM bank previously selected by a DCL instruction.
     *   yy   - 1 of 4 registers within the DATA RAM chip.
     *   zzzz - 1 of 16 4-bit data characters within the register
     */

    int bank = cpu->getDcl();
    int chip = (cpu->getSrc() & 0b11000000) >> 6;
    int reg = (cpu->getSrc() & 0b00110000) >> 4;
    int character = (cpu->getSrc() & 0xF);

    int value = dram->getDataRAMBank(bank)->getDataRAMChip(chip)->
            getDataRAMRegister(reg)->getCharacter(character);
    cpu->setAcc(value);

    cpu->setPC(cpu->getPC() + 1);
    cpu->setCycles(cpu->getCycles() + 1);
}

/**
 * @brief Simulator::RDR - READ ROM PORT
 */
void Simulator::RDR()
{
    /*
     * READ ROM PORT
     *
     * 1110 1010
     *
     * The ROM port specified by the last SRC instruction is read. When using the 4001
     * ROM, each of the 4 lines of the port may be an input or an output line; the data on
     * the input lines is transferred to the corresponding bits of the accumulator. Any
     * output lines cause either a 0 or a 1 to be transferred to the corresponding bits of
     * the accumulator. Whether a 0 or a 1 is transferred is a function of the hardware,
     * not under control of the programmer.
     *
     * The carry bit is not affected.
     */

    /*
     * The 8 bits of the address sent by the SRC are interpreted as follows:
     *
     * When referencing a ROM input or output port:
     *   xxxxyyyy
     *   xxxx - The port associated with 1 of 16 ROM's.
     *   yyyy - These bits are not relevant for this reference.
     */

    int port = (cpu->getSrc() & 0xF0) >> 4;
    cpu->setAcc(rom->getIO(port));

    cpu->setPC(cpu->getPC() + 1);
    cpu->setCycles(cpu->getCycles() + 1);
}

/**
 * @brief Simulator::ADM - ADD DATA RAM TO ACCUMULATOR WITH CARRY
 */
void Simulator::ADM()
{
    /*
     * ADD DATA RAM TO ACCUMULATOR WITH CARRY
     *
     * 1110 1011
     *
     * The DATA RAM data character specified by the last SRC instruction, plus the
     * carry bit, are added to the accumulator.
     *
     * The carry bit will be set if the result generates a carry, and will be reset otherwise.
     *
     * The data character is not affected.
     */

    /*
     * The 8 bits of the address sent by the SRC are interpreted as follows:
     *
     * When referencing a DATA RAM data character:
     *   xxyyzzzz
     *   xx   - 1 of 4 DATA RAM chips within the DATA RAM bank previously selected by a DCL instruction.
     *   yy   - 1 of 4 registers within the DATA RAM chip.
     *   zzzz - 1 of 16 4-bit data characters within the register
     */

    int bank = cpu->getDcl();
    int chip = (cpu->getSrc() & 0b11000000) >> 6;
    int reg = (cpu->getSrc() & 0b00110000) >> 4;
    int character = cpu->getSrc() & 0xF;

    int memValue = dram->getDataRAMBank(bank)->getDataRAMChip(chip)->
            getDataRAMRegister(reg)->getCharacter(character);

    int result = memValue + cpu->getCarry() + cpu->getAcc();
    cpu->setAcc(result % 0x10);
    cpu->setCarry((result & 0b10000) >> 4);

    cpu->setPC(cpu->getPC() + 1);
    cpu->setCycles(cpu->getCycles() + 1);
}

/**
 * @brief Simulator::RD0 - READ DATA RAM STATUS CHARACTER 0
 */
void Simulator::RD0()
{
    /*
     * READ DATA RAM STATUS CHARACTER
     *
     * Description is the same for RD0, RD1, RD2, RD3
     *
     * 1110 11xx
     * xx - number of a status character
     * 00 - RD0
     * 01 - RD1
     * 10 - RD2
     * 11 - RD3
     *
     * The DATA RAM status character whose number from 0 to 3 is specified by n, associated
     * with the DATA RAM register specified by the last SRC instruction, is loaded
     * into the accumulator.
     *
     * The carry bit and the status character are not affected.
     */

    /*
     * The 8 bits of the address sent by the SRC are interpreted as follows:
     *
     * When referencing a DATA RAM status character:
     *   xxyyzzzz
     *   xx   - 1 of 4 DATA RAM chips within the DATA RAM bank previously selected by a DCL instruction.
     *   yy   - 1 of 4 registers within the DATA RAM chip.
     *   zzzz - These bits are not relevant for this reference.
     */

    int bank = cpu->getDcl();
    int chip = (cpu->getSrc() & 0b11000000) >> 6;
    int reg = (cpu->getSrc() & 0b00110000) >> 4;

    int value = dram->getDataRAMBank(bank)->getDataRAMChip(chip)->
            getDataRAMRegister(reg)->getStatus(0);
    cpu->setAcc(value);

    cpu->setPC(cpu->getPC() + 1);
    cpu->setCycles(cpu->getCycles() + 1);
}

/**
 * @brief Simulator::RD1 - READ DATA RAM STATUS CHARACTER 1
 */
void Simulator::RD1()
{
    /*
     * For description see RD0 function
     */

    int bank = cpu->getDcl();
    int chip = (cpu->getSrc() & 0b11000000) >> 6;
    int reg = (cpu->getSrc() & 0b00110000) >> 4;

    int value = dram->getDataRAMBank(bank)->getDataRAMChip(chip)->
            getDataRAMRegister(reg)->getStatus(1);
    cpu->setAcc(value);

    cpu->setPC(cpu->getPC() + 1);
    cpu->setCycles(cpu->getCycles() + 1);
}

/**
 * @brief Simulator::RD2 - READ DATA RAM STATUS CHARACTER 2
 */
void Simulator::RD2()
{
    /*
     * For description see RD0 function
     */

    int bank = cpu->getDcl();
    int chip = (cpu->getSrc() & 0b11000000) >> 6;
    int reg = (cpu->getSrc() & 0b00110000) >> 4;

    int value = dram->getDataRAMBank(bank)->getDataRAMChip(chip)->
            getDataRAMRegister(reg)->getStatus(2);
    cpu->setAcc(value);

    cpu->setPC(cpu->getPC() + 1);
    cpu->setCycles(cpu->getCycles() + 1);
}

/**
 * @brief Simulator::RD3 - READ DATA RAM STATUS CHARACTER 3
 */
void Simulator::RD3()
{
    /*
     * For description see RD0 function
     */

    int bank = cpu->getDcl();
    int chip = (cpu->getSrc() & 0b11000000) >> 6;
    int reg = (cpu->getSrc() & 0b00110000) >> 4;

    int value = dram->getDataRAMBank(bank)->getDataRAMChip(chip)->
            getDataRAMRegister(reg)->getStatus(3);
    cpu->setAcc(value);

    cpu->setPC(cpu->getPC() + 1);
    cpu->setCycles(cpu->getCycles() + 1);
}

/**
 * @brief Simulator::CLB - CLEAR BOTH
 */
void Simulator::CLB()
{
    /*
     * CLEAR BOTH
     *
     * 1111 0000
     *
     * The accumulator is set to 0000B, and the carry bit is reset.
     */

    cpu->setAcc(0);
    cpu->setCarry(0);

    cpu->setPC(cpu->getPC() + 1);
    cpu->setCycles(cpu->getCycles() + 1);
}

/**
 * @brief Simulator::CLC - CLEAR CARRY
 */
void Simulator::CLC()
{
    /*
     * CLEAR CARRY
     *
     * 1111 0001
     *
     * The carry bit is reset to 0.
     */

    cpu->setCarry(0);

    cpu->setPC(cpu->getPC() + 1);
    cpu->setCycles(cpu->getCycles() + 1);
}

/**
 * @brief Simulator::IAC - INCREMENT ACCUMULATOR
 */
void Simulator::IAC()
{
    /*
     * INCREMENT ACCUMULATOR
     *
     * 1111 0010
     *
     * The contents of the accumulator are incremented by one. The carry bit is set if
     * there is a carry out of the high order bit position 1 and reset if there is no carry.
     */

    int acc = cpu->getAcc() + 1;

    cpu->setAcc(acc & 0xF);
    cpu->setCarry((acc & 0b10000) >> 4);

    cpu->setPC(cpu->getPC() + 1);
    cpu->setCycles(cpu->getCycles() + 1);
}

/**
 * @brief Simulator::CMC - COMPLEMENT CARRY
 */
void Simulator::CMC()
{
    /*
     * COMPLEMENT CARRY
     *
     * 1111 0011
     *
     * If the carry bit = 0, it is set to 1. If the carry bit is = 1, it is set to O.
     */

    int carry = cpu->getCarry();
    carry = carry == 0 ? 1 : 0;
    cpu->setCarry(carry);

    cpu->setPC(cpu->getPC() + 1);
    cpu->setCycles(cpu->getCycles() + 1);
}

/**
 * @brief Simulator::CMA - COMPLEMENT ACCUMULATOR
 */
void Simulator::CMA()
{
    /*
     * COMPLEMENT ACCUMULATOR
     *
     * 1111 0100
     *
     * Each bit of the contents of the accumulator is complemented (produ-cing the socalled
     * one's complement).
     *
     * The carry bit is not affected.
     */

    int acc = ~cpu->getAcc();
    cpu->setAcc(acc & 0xF);

    cpu->setPC(cpu->getPC() + 1);
    cpu->setCycles(cpu->getCycles() + 1);
}

/**
 * @brief Simulator::RAL - ROTATE ACCUMULATOR LEFT THROUGH CARRY
 */
void Simulator::RAL()
{
    /*
     * ROTATE ACCUMULATOR LEFT THROUGH CARRY
     *
     * 1111 0101
     *
     * The contents of the accumulator are rotated one bit position to the left.
     *
     * The high-order bit of the accumulator replaces the carry bit I while the carry bit
     * replaces the low-order bit of the accumulator.
     */

    int acc = cpu->getAcc();
    int carry = cpu->getCarry();

    cpu->setAcc(((acc << 1) | carry) & 0xF);
    cpu->setCarry((acc & 0b1000) >> 3);

    cpu->setPC(cpu->getPC() + 1);
    cpu->setCycles(cpu->getCycles() + 1);
}

/**
 * @brief Simulator::RAR - ROTATE ACCUMULATOR RIGHT THROUGH CARRY
 */
void Simulator::RAR()
{
    /*
     * ROTATE ACCUMULATOR RIGHT THROUGH CARRY
     *
     * 1111 0110
     *
     * The contents of the accumulator are rotated one bit position to the right.
     *
     * The low-order bit of the accumulator replaces the carry bit, while the carry bit
     * replaces the high-order bit of the accumulator.
     */

    int acc = cpu->getAcc();
    int carry = cpu->getCarry();

    cpu->setAcc((acc >> 1) | (carry << 3));
    cpu->setCarry(acc & 0x1);

    cpu->setPC(cpu->getPC() + 1);
    cpu->setCycles(cpu->getCycles() + 1);
}

/**
 * @brief Simulator::TCC - TRANSMIT CARRY AND CLEAR
 */
void Simulator::TCC()
{
    /*
    * TRANSMIT CARRY AND CLEAR
    *
    * 1111 0111
    *
    * If the carry bit = 0, the accumulator is set to 0000B. If the carry bit = 1, the
    * accumulator is set to 0001B. In either case, the carry bit is then reset.
    */

    if (cpu->getCarry() == 0)
    {
        cpu->setAcc(0);
    }
    else
    {
        cpu->setAcc(1);
    }
    cpu->setCarry(0);

    cpu->setPC(cpu->getPC() + 1);
    cpu->setCycles(cpu->getCycles() + 1);
}

/**
 * @brief Simulator::DAC - DECREMENT ACCUMULATOR
 */
void Simulator::DAC()
{
    /*
     * DECREMENT ACCUMULATOR
     *
     * 1111 1000
     *
     * The contents of the accumulator are decremented by one. The carry bit is set
     * if there is no borrow out of the high-order bit position 1 and reset if there is a
     * borrow.
     *
     * F.e.:
     * acc = 1001B
     *    1001
     *  + 1111
     *   10000
     *   \\acc = 0000
     *    \carry = 1
     *
     * acc = 0000B
     *    0000
     *  + 1111
     *   01111
     *   \\acc = 1111
     *    \carry = 0
     *
     */

    int acc = cpu->getAcc() + 0xF;

    cpu->setAcc(acc & 0xF);
    cpu->setCarry((acc & 0b10000) >> 4);

    cpu->setPC(cpu->getPC() + 1);
    cpu->setCycles(cpu->getCycles() + 1);
}

/**
 * @brief Simulator::TCS - TRANSFER CARRY SUBTRACT
 */
void Simulator::TCS()
{
    /*
     * TRANSFER CARRY SUBTRACT
     *
     * 1111 1001
     *
     * If the carry bit = 0, the accumulator is set to 9. If the carry bit = 1, the
     * accumulator is set to 10. In either case, the carry bit is then reset.
     */

    if (cpu->getCarry() == 0)
    {
        cpu->setAcc(0x9);
    }
    else
    {
        cpu->setAcc(0xA);
    }
    cpu->setCarry(0);

    cpu->setPC(cpu->getPC() + 1);
    cpu->setCycles(cpu->getCycles() + 1);
}

/**
 * @brief Simulator::STC - SET CARRY
 */
void Simulator::STC()
{
    /*
     * SET CARRY
     *
     * 1111 1010
     *
     * The carry bit is set to 1.
     */

    cpu->setCarry(1);

    cpu->setPC(cpu->getPC() + 1);
    cpu->setCycles(cpu->getCycles() + 1);
}

/**
 * @brief Simulator::DAA - DECIMAL ADJUST ACCUMULATOR
 */
void Simulator::DAA()
{
    /*
     * DECIMAL ADJUST ACCUMULATOR
     *
     * 1111 1011
     *
     * If the contents of the accumulator are greater than 9, or if the carty bit = 1,
     * the accumulator is incremented by 6. Otherwise, the accumulator is not affected.
     * If the result of incrementing the accumulator produces a carry out of the high order
     * bit position, the carry bit is set. Otherwise the carry bit is unaffected (in particular,
     * it is not reset).
     */

    if (cpu->getAcc() > 9 || cpu->getCarry())
    {
        int acc = cpu->getAcc() + 6;
        if (acc > 0xF)
        {
            cpu->setCarry(1);
        }
        cpu->setAcc(acc % 0x10);
    }

    cpu->setPC(cpu->getPC() + 1);
    cpu->setCycles(cpu->getCycles() + 1);
}

/**
 * @brief Simulator::KBP - KEYBOARD PROCESS
 */
void Simulator::KBP()
{
    /*
     * KEYBOARD PROCESS
     *
     * 1111 1100
     *
     * If the accumulator contains 0000B, it remains unchanged. If one bit of the accumulator
     * is set, the accumulator is set to a number from 1 to 4 indicating which bit was
     * set.
     *
     * If more than one bit of the accumulator is set, the accumulator is set to 1111 B.
     */

    switch(cpu->getAcc())
    {
    case 0x0:
        // do nothing
        break;
    case 0x1:
        cpu->setAcc(0x1);
        break;
    case 0x2:
        cpu->setAcc(0x2);
        break;
    case 0x3:
        cpu->setAcc(0xF);
        break;
    case 0x4:
        cpu->setAcc(0x3);
        break;
    case 0x5:
        cpu->setAcc(0xF);
        break;
    case 0x6:
        cpu->setAcc(0xF);
        break;
    case 0x7:
        cpu->setAcc(0xF);
        break;
    case 0x8:
        cpu->setAcc(0x4);
        break;
    case 0x9:
        cpu->setAcc(0xF);
        break;
    case 0xA:
        cpu->setAcc(0xF);
        break;
    case 0xB:
        cpu->setAcc(0xF);
        break;
    case 0xC:
        cpu->setAcc(0xF);
        break;
    case 0xD:
        cpu->setAcc(0xF);
        break;
    case 0xE:
        cpu->setAcc(0xF);
        break;
    case 0xF:
        cpu->setAcc(0xF);
        break;
    }

    cpu->setPC(cpu->getPC() + 1);
    cpu->setCycles(cpu->getCycles() + 1);
}

/**
 * @brief Simulator::DCL - DESIGNATE COMMAND LINE
 */
void Simulator::DCL()
{
    /*
     * DESIGNATE COMMAND LINE
     *
     * The DCL instruction occupies one byte.
     *
     * 1111 1101
     *
     * The DCL instruction uses the rightmost 3 bits of the accumulator to determine
     * which of the 8 DATA RAM BANKS will be referenced during subsequent operations.
     */
    cpu->setDcl(cpu->getAcc() & 0x7);

    cpu->setPC(cpu->getPC() + 1);
    cpu->setCycles(cpu->getCycles() + 1);
}
