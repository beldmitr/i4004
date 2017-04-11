/*
 * SourceCode.cpp
 *
 *  Created on: 16. 8. 2016
 *      Author: user
 */

#include "Compiler.h"

// TODO Error Stream
// TODO Maybe to do Error Class
// TODO toCompile method divide to several methods
// TODO Checking Labels. They can't be the same as the names of the instructions, registers, pairs and other keywords
// TODO Format of a pair maybe P0, p0 and 0P, 0p. Maybe to do 0P and 0p format too.
// TODO Format of a register maybe R0, r0 and 0R, 0r. Maybe to do 0R and 0r format too.

Compiler::Compiler(const std::string& filename, const std::string& output)
{

    this->output = output;

    sourcefile.open(filename.c_str(), ios::in);

    if (sourcefile.is_open())
    {
        std::string line;

        while (getline(sourcefile, line))
        {
            code.push_back(line);
        }

    }
    else
    {
        sourcefile.close();
        std::string msg = "File " + filename + " can't be open.";
        throw msg;
    }

}

Compiler::~Compiler()
{
    sourcefile.close();
}

Compiler::Instruct::Instruct(std::string name, std::string operandLeft,std::string operandRight,
                                   std::string line, int lineNumber, int code)
    : name(name), operandLeft(operandLeft), operandRight(operandRight),
      line(line), lineNumber(lineNumber), code(code)
{

}

std::string Compiler::getConstByLabel(const std::string& label)
{
    for (const Constants& c : constantsTable)
    {
        if (label == c.label)
        {
            if (Utils::Number::isNumber(c.constant))
            {
                return c.constant;
            }
            else if (Instruction::Operand::isLabel(c.constant) && !c.constant.empty())
            {
                return getConstByLabel(c.constant);
            }
        }
    }

    // write error
    //    stringstream s;
    //    s << "Can't resolve label value " << label << endl;
    //    errList->addItem(QString::fromStdString(s.str()));
    //    errors.push_back({-1, "Can't resolve label value ", label});
    return "";
}

int Compiler::getAddressByLabel(const std::string& label)
{
    for (const Labels& l : labelsTable)
    {
        if (l.label == label)
        {
            return l.address;
        }
    }

    return -1;
}

bool Compiler::checkLabelExist(const std::string& label)
{
    for (const Labels& l : labelsTable)
    {
        if (label == l.label)
        {
            return true;
        }
    }

    for (const Constants& c : constantsTable)
    {
        if (label == c.label)
        {
            return true;
        }
    }

    return false;
}

void Compiler::saveToTables(const std::string& line, const std::string& label,
                            const std::string& instruction, const std::string& operandLeft,
                            const std::string& operandRight, const int& lineNumber, const int& address)
{
    /*
     *  Save data to tables
     *
     *  Num Label Operator LeftOperand RightOperand Describe
     *  0    0     0        0           0            OK, just empty line or there is a comment
     *  1    0     0        0           1            ERROR, only RightOperand
     *  2    0     0        1           0            ERROR, only LeftOperand
     *  3    0     0        1           1            ERROR, only Operands
     *  4    0     1        0           0            OK, F.e.: WR0
     *  5    0     1        0           1            ERROR, Must be LeftOperand
     *  6    0     1        1           0            OK, F.e.: JUN 23
     *  7    0     1        1           1            OK, F.e.: FIM P0, 23
     *  8    1     0        0           0            ERROR, Label to an empty line
     *  9    1     0        0           1            ERROR, Label to RightOperand
     *  A    1     0        1           0            OK, F.e.: ABC, 23
     *  B    1     0        1           1            ERROR, Label to Operands
     *  C    1     1        0           0            OK, F.e.: ABC, WR0
     *  D    1     1        0           1            ERROR, Must be LeftOperand
     *  E    1     1        1           0            OK, F.e.: ABC, JUN 23
     *  F    1     1        1           1            OK, F.e.: ABC, FIM P1, 23
     *
     */

    if (label == "" && instruction == "" && operandLeft == "" && operandRight == "")
    {
        /*
         * Case 0
         * If line is empty, then nothing to do
         */
    }
    else if (label == "" && instruction == "" && operandLeft == "" && operandRight != "")
    {
        /*
         *	Case 1
         */

        // write error
        //        stringstream s;
        //        s << "Error at line " << lineNumber << ": Instruction expected, but left operand was acquired (1). Line: "
        //                << trim(line) << endl;
        //        errList->addItem(QString::fromStdString(s.str()));
        errors.push_back( { lineNumber,  "Instruction expected, but left operand was acquired (1).", Utils::String::trim(line)} );
    }
    else if (label == "" && instruction == "" && operandLeft != "" && operandRight == "")
    {
        /*
         *	Case 2
         */

        // write error
        //        stringstream s;
        //        s << "Error at line " << lineNumber << ": Instruction expected, but right operand was acquired (2). Line: "
        //                << trim(line) << endl;
        //        errList->addItem(QString::fromStdString(s.str()));
        errors.push_back( { lineNumber,  "Instruction expected, but right operand was acquired (2).", Utils::String::trim(line)} );
    }
    else if (label == "" && instruction == "" && operandLeft != "" && operandRight != "")
    {
        /*
         *	Case 3
         */

        // write error
        //        stringstream s;
        //        s << "Error at line " << lineNumber << ": Instruction expected, but both operands was acquired (3). Line: "
        //                << trim(line) << endl; // TODO Delete this cout
        //        errList->addItem(QString::fromStdString(s.str()));
        errors.push_back( { lineNumber,  "Instruction expected, but both operands was acquired (3).", Utils::String::trim(line)} );
    }
    else if (label == "" && instruction != "" && operandLeft == "" && operandRight == "")
    {
        /*
         *	Case 4
         * 	if a line has only instruction and no label
         *	For example:
         *	WR0
         * 	So it only writes the command to the instructionTable
         */

        instructionTable.push_back( { instruction, operandLeft, operandRight, Utils::String::trim(line), lineNumber, -1 });
    }
    else if (label == "" && instruction != "" && operandLeft == "" && operandRight != "")
    {
        /*
         *	Case 5
         *	ERROR, Must be LeftOperand
         */

        // write error
        //        stringstream s;
        //        s << "Error at line " << lineNumber << ": Left operand acquired (5). Line: " << trim(line) << endl;
        //        errList->addItem(QString::fromStdString(s.str()));
        errors.push_back( { lineNumber,  "Left operand acquired (5).", Utils::String::trim(line)} );
    }
    else if (label == "" && instruction != "" && operandLeft != "" && operandRight == "")
    {
        /*
         *	Case 6
         * 	if a line has only instruction and no label
         *	For example:
         * 	JUN 30
         * 	So it only writes the command to the instructionTable
         */

        instructionTable.push_back( { instruction, operandLeft, operandRight, Utils::String::trim(line), lineNumber, -1 });
    }
    else if (label == "" && instruction != "" && operandLeft != "" && operandRight != "")
    {
        /*
         *	Case 7
         * 	if a line has only instruction and no label
         *	For example:
         * 	FIM P1, 45
         * 	So it only writes the command to the instructionTable
         */

        instructionTable.push_back( { instruction, operandLeft, operandRight, Utils::String::trim(line), lineNumber, -1 });
    }
    else if (label != "" && instruction == "" && operandLeft == "" && operandRight == "")
    {
        /*
         *	Case 8
         */

        // write error
        //        stringstream s;
        //        s << "Error at line " << lineNumber << ": Label to an empty line (8). Line: " << trim(line) << endl;
        //        errList->addItem(QString::fromStdString(s.str()));
        errors.push_back( { lineNumber,  "Label to an empty line (8).", Utils::String::trim(line)} );
    }
    else if (label != "" && instruction == "" && operandLeft == "" && operandRight != "")
    {
        /*
         *	Case 9
         */

        // write error
        //        stringstream s;
        //        s << "Error at line " << lineNumber << ": Label to right operand (9). Line: " << trim(line) << endl;
        //        errList->addItem(QString::fromStdString(s.str()));
        errors.push_back( { lineNumber,  "Label to right operand (9).", Utils::String::trim(line)} );
    }
    else if (label != "" && instruction == "" && operandLeft != "" && operandRight == "")
    {
        /*
         *	Case A
         * 	if format of a line is
         * 	Label, constant
         * 	For example:
         * 	ABC, 23
         * 	AAA, 50H
         * 	So to a label will be written a constant
         */

        constantsTable.push_back( { label, operandLeft });
    }
    else if (label != "" && instruction == "" && operandLeft != "" && operandRight != "")
    {
        /*
         *	Case B
         */

        // write error
        //        stringstream s;
        //        s << "Error at line " << lineNumber << ": Label to both operands (B). Line: " << trim(line) << endl;
        //        errList->addItem(QString::fromStdString(s.str()));
        errors.push_back( { lineNumber,  "Label to both operands (B).", Utils::String::trim(line)} );
    }
    else if (label != "" && instruction != "" && operandLeft == "" && operandRight == "")
    {
        /*
         *	Case C
         *	if a line has a label
         *	Label, Instruction Operand
         *	For example:
         *	AAA, WR0
         *	So label consider an address
         */

        labelsTable.push_back( { label, address });
        instructionTable.push_back( { instruction, operandLeft, operandRight, Utils::String::trim(line), lineNumber, -1 });
    }
    else if (label != "" && instruction != "" && operandLeft == "" && operandRight != "")
    {
        /*
         * Case D
         * ERROR, Must be LeftOperand
         */

        // write error
        //        stringstream s;
        //        s << "Error at line " << lineNumber << ": Expected left operand (D). Line: " << trim(line) << endl;
        //        errList->addItem(QString::fromStdString(s.str()));
        errors.push_back( { lineNumber,  "Expected left operand (D).", Utils::String::trim(line)} );
    }
    else if (label != "" && instruction != "" && operandLeft != "" && operandRight == "")
    {
        /*
         *	Case E
         *	if a line has a label
         *	Label, Instruction Operand
         *	For example:
         *	ABC, JUN 20H
         *	So label consider an address
         */

        labelsTable.push_back( { label, address });
        instructionTable.push_back( { instruction, operandLeft, operandRight, Utils::String::trim(line), lineNumber, -1 });
    }
    else if (label != "" && instruction != "" && operandLeft != "" && operandRight != "")
    {
        /*
         *	Case F
         *	if a line has a label
         *	Label, Instruction Operand
         *	For example:
         *	BBC, FIM P0, 50
         *	So label consider an address
         */

        labelsTable.push_back( { label, address });
        instructionTable.push_back( { instruction, operandLeft, operandRight, Utils::String::trim(line), lineNumber, -1 });
    }
    else
    {
        /*
         *  TODO write an error to ErrorStream
         *  Here is some unexpected error
         */

        // write error
        //        stringstream s;
        //        s << "Error at line " << lineNumber << ": Unexpected error. Line: " << trim(line) << endl;
        //        errList->addItem(QString::fromStdString(s.str()));
        errors.push_back( { lineNumber,  "Unexpected error.", Utils::String::trim(line)} );
    }
}

void Compiler::parseLine(std::string& line, std::string& label, std::string& instruction,
                         std::string& operand, std::string& operandLeft, std::string& operandRight,
                         const int& lineNumber)
{
    std::string currentLine = Utils::String::trim(line);
    smatch m;
    // Find and delete from line a comment, if it exists

    if (Utils::Assembler::Line::searchComment(line, m))
    {
        line = m.prefix().str();	// We don't need a comment in ObjectCode, so only delete it
    }

    // Parse a label
    if (Utils::Assembler::Line::searchLabel(line, m))
    {
        label = Utils::String::trimStrong(m[0]);	// A label on a line
        label = regex_replace(label, regex("(,)"), "");	// Delete "," from label
        line = m.suffix().str();

        std::string prefix = m.prefix().str();
        // Check if something is by left side of a label. If it is, then this is error
        if (!Utils::String::trimStrong(prefix).empty())
        {
            // write error
            //            stringstream s;
            //            s << "Error at line " << lineNumber << ": Wrong label \"" << prefix << "\". Line: " << currentLine
            //                    << endl;
            //            errList->addItem(QString::fromStdString(s.str()));
            errors.push_back( { lineNumber,  "Wrong label \"" + prefix + "\".", currentLine} );
        }

        /*
         *  Check if label exists.
         *  If exists, it throws error
         */
        if (checkLabelExist(label))
        {
            // write error
            //            stringstream s;
            //            s << "Error at line " << lineNumber << ": Label " << label << " exists. Line: " << currentLine << endl;// TODO Delete cout after implementing error stream
            //            errList->addItem(QString::fromStdString(s.str()));
            errors.push_back( { lineNumber,  "Label \"" + label + "\" exists.", currentLine} );
        }
    }

    /*
     *  It resolve constants with expression
     *  Label, 23+AAA
     */
    if (Instruction::Operand::searchMathExpression(line, m) && !Instruction::CommandSet::isCommand(m[0])) // TODO maybe do this better, I don't like this logic, why I check isExistCommand??
    {
        operandLeft = Utils::String::trimStrong(m[0]);
        return;
    }

    // Parse an instruction
    if (Utils::Assembler::Line::searchInstruction(line, m))
    {
        instruction = Utils::String::trimStrong(m[0]);	// An instruction on a line
        line = m.suffix().str();
    }

    // Parse operand(s)
    if (Utils::Assembler::Line::searchOperand(line, m))
    {
        operand = m[0];	//	Operand
        line = m.suffix().str();

        // Divide operand to left and right, if they exist
        operandLeft = Utils::String::trimStrong(operand);
        if (regex_search(operand, m, regex("(,)")))
        {
            operandLeft = Utils::String::trimStrong(m.prefix().str());
            operandRight = Utils::String::trimStrong(m.suffix().str());
        }
    }

    /*
     * If line is not empty, that means, that compiler couldn't resolve something,
     * so we should to throw an error to the error stream
     */
    if (!Utils::String::trimStrong(line).empty())
    {

        // write error
        //        stringstream s;
        //        s << "Error at line " << lineNumber << ". Can't resolve " << line << ". Line: " << currentLine << endl;
        //        errList->addItem(QString::fromStdString(s.str()));
        errors.push_back( { lineNumber,  "Can't resolve \"" + line + "\".", currentLine} );
    }
}

void Compiler::preprocessing()
{
    // Evaluate constant labels
    for (Constants& c : constantsTable)
    {
        if (Instruction::Operand::isLabel(c.constant))
        {
            c.constant = getConstByLabel(c.constant);
        }
    }

    for (Instruct& instr : instructionTable)
    {
        /*
         * Check instructions
         * if don't exist or if they have got wrong operands
         */
        switch (Instruction::CommandSet::getCommand(instr.name))
        {
        case 0x0:
            checkNoOperands(instr);
            break;
        case 0x1000: // Jump Conditional	JCN	0001CCCC	AAAAAAAA	condition, address
            checkLeftOperandCondition(instr);
            checkRightOperandAddress(instr);
            break;
        case 0x2000: //Fetch Immediate	FIM	0010RRR0	DDDDDDDD	register pair, data
            checkLeftOperandPair(instr);
            checkRightOperandData(instr);
            break;
        case 0x21: //Send Register Control	SRC	0010RRR1	-	register pair
            checkLeftOperandPair(instr);
            checkNoRightOperand(instr);
            break;
        case 0x30: //Fetch Indirect	FIN	0011RRR0	-	register pair
            checkLeftOperandPair(instr);
            checkNoRightOperand(instr);
            break;
        case 0x31: //Jump Indirect	JIN	0011RRR1	-	register pair
            checkLeftOperandPair(instr);
            checkNoRightOperand(instr);
            break;
        case 0x4000: //Jump Unconditional	JUN	0100AAAA	AAAAAAAA	address
            checkLeftOperandAddress(instr);
            checkNoRightOperand(instr);
            break;
        case 0x5000: //Jump to Subroutine	JMS	0101AAAA	AAAAAAAA	address
            checkLeftOperandAddress(instr);
            checkNoRightOperand(instr);
            break;
        case 0x60: //Increment	INC	0110RRRR	-	register
            checkLeftOperandRegister(instr);
            checkNoRightOperand(instr);
            break;
        case 0x7000: //Increment and Skip	ISZ	0111RRRR	AAAAAAAA	register, address
            checkLeftOperandRegister(instr);
            checkRightOperandAddress(instr);
            break;
        case 0x80: //Add	ADD	1000RRRR	-	register
            checkLeftOperandRegister(instr);
            checkNoRightOperand(instr);
            break;
        case 0x90: //Subtract	SUB	1001RRRR	-	register
            checkLeftOperandRegister(instr);
            checkNoRightOperand(instr);
            break;
        case 0xA0: //Load	LD	1010RRRR	-	register
            checkLeftOperandRegister(instr);
            checkNoRightOperand(instr);
            break;
        case 0xB0: //Exchange	XCH	1011RRRR	-	register
            checkLeftOperandRegister(instr);
            checkNoRightOperand(instr);
            break;
        case 0xC0: //Branch Back and Load	BBL	1100DDDD	-	data
            checkLeftOperandData(instr);
            checkNoRightOperand(instr);
            break;
        case 0xD0: //Load Immediate	LDM	1101DDDD	-	data
            checkLeftOperandData(instr);
            checkNoRightOperand(instr);
            break;
        case 0xE0: //Write Main Memory	WRM	11100000	-	none
            checkNoOperands(instr);
            break;
        case 0xE1: //Write RAM Port	WMP	11100001	-	none
            checkNoOperands(instr);
            break;
        case 0xE2: //Write ROM Port	WRR	11100010	-	none
            checkNoOperands(instr);
            break;
        case 0xE4: //Write Status Char 0	WR0	11100100	-	none
            checkNoOperands(instr);
            break;
        case 0xE5: //Write Status Char 1	WR1	11100101	-	none
            checkNoOperands(instr);
            break;
        case 0xE6: //Write Status Char 2	WR2	11100110	-	none
            checkNoOperands(instr);
            break;
        case 0xE7: //Write Status Char 3	WR3	11100111	-	none
            checkNoOperands(instr);
            break;
        case 0xE8: //Subtract Main Memory	SBM	11101000	-	none
            checkNoOperands(instr);
            break;
        case 0xE9: //Read Main Memory	RDM	11101001	-	none
            checkNoOperands(instr);
            break;
        case 0xEA: //Read ROM Port	RDR	11101010	-	none
            checkNoOperands(instr);
            break;
        case 0xEB: //Add Main Memory	ADM	11101011	-	none
            checkNoOperands(instr);
            break;
        case 0xEC: //Read Status Char 0	RD0	11101100	-	none
            checkNoOperands(instr);
            break;
        case 0xED: //Read Status Char 1	RD1	11101101	-	none
            checkNoOperands(instr);
            break;
        case 0xEE: //Read Status Char 2	RD2	11101110	-	none
            checkNoOperands(instr);
            break;
        case 0xEF: //Read Status Char 3	RD3	11101111	-	none
            checkNoOperands(instr);
            break;
        case 0xF0: //Clear Both	CLB	11110000	-	none
            checkNoOperands(instr);
            break;
        case 0xF1: //Clear Carry	CLC	11110001	-	none
            checkNoOperands(instr);
            break;
        case 0xF2: //Increment Accumulator	IAC	11110010	-	none
            checkNoOperands(instr);
            break;
        case 0xF3: //Complement Carry	CMC	11110011	-	none
            checkNoOperands(instr);
            break;
        case 0xF4: //Complement	CMA	11110100	-	none
            checkNoOperands(instr);
            break;
        case 0xF5: //Rotate Left	RAL	11110101	-	none
            checkNoOperands(instr);
            break;
        case 0xF6: //Rotate Right	RAR	11110110	-	none
            checkNoOperands(instr);
            break;
        case 0xF7: //Transfer Carry and Clear	TCC	11110111	-	none
            checkNoOperands(instr);
            break;
        case 0xF8: //Decrement Accumulator	DAC	11111000	-	none
            checkNoOperands(instr);
            break;
        case 0xF9: //Transfer Carry Subtract	TCS	11111001	-	none
            checkNoOperands(instr);
            break;
        case 0xFA: //Set Carry	STC	11111010	-	none
            checkNoOperands(instr);
            break;
        case 0xFB: //Decimal Adjust Accumulator	DAA	11111011	-	none
            checkNoOperands(instr);
            break;
        case 0xFC: //Keyboard Process	KBP	11111100	-	none
            checkNoOperands(instr);
            break;
        case 0xFD: //Designate Command Line	DCL	11111101	-	none
            checkNoOperands(instr);
            break;

        default:
            //write error
            //            stringstream s;
            //            s << "Error at line " << instr.lineNumber << ": Instruction " << instr.name << " doesn't exist. Line: "
            //                    << instr.line << endl;
            //            errList->addItem(QString::fromStdString(s.str()));
            errors.push_back( { instr.lineNumber,  "Instruction \"" + instr.name + "\" doesn't exist.", instr.line} );
            break;
        }

    }	// for
}

void Compiler::composing()
{
    for (Instruct& instr : instructionTable)
    {
        int op1 = 0;
        int op2 = 0;
        /*
         * Compose instructions to object code
         */
        switch (Instruction::CommandSet::getCommand(instr.name))
        {
        case 0x0:
            instr.code = 0x0;
            break;
        case 0x1000: // Jump Conditional	JCN	0001CCCC	AAAAAAAA	condition, address
            op1 = Utils::Convert::condition2int(instr.operandLeft);
            op2 = Utils::Convert::address2int(instr.operandRight);
            instr.code = ((0x1000 | (Utils::Convert::to4bit(op1) << 8)) | Utils::Convert::to8bit(op2)) & 0xFFFF;
            break;
        case 0x2000: //Fetch Immediate	FIM	0010RRR0	DDDDDDDD	register pair, data
            op1 = Utils::Convert::pair2int(instr.operandLeft);
            op2 = Utils::Convert::dec2int(instr.operandRight);
            instr.code = ((0x2000 | (op1 << 9)) | Utils::Convert::to8bit(op2)) & 0xFFFF;    // TODO (op1 << 9) why 9 ??? why not 8 ???? check it
            break;
        case 0x21: //Send Register Control	SRC	0010RRR1	-	register pair
            op1 = Utils::Convert::pair2int(instr.operandLeft);
            instr.code = (0x21 | (op1 << 1)) & 0xFF;
            break;
        case 0x30: //Fetch Indirect	FIN	0011RRR0	-	register pair
            op1 = Utils::Convert::pair2int(instr.operandLeft);
            instr.code = (0x30 | (op1 << 1)) & 0xFF;
            break;
        case 0x31: //Jump Indirect	JIN	0011RRR1	-	register pair
            op1 = Utils::Convert::pair2int(instr.operandLeft);
            instr.code = (0x31 | (op1 << 1)) & 0xFF;
            break;
        case 0x4000: //Jump Unconditional	JUN	0100AAAA	AAAAAAAA	address
            op1 = Utils::Convert::address2int(instr.operandLeft);
            instr.code = (0x4000 | Utils::Convert::to12bit(op1)) & 0xFFFF;
            break;
        case 0x5000: //Jump to Subroutine	JMS	0101AAAA	AAAAAAAA	address
            op1 = Utils::Convert::address2int(instr.operandLeft);
            instr.code = (0x5000 | Utils::Convert::to12bit(op1)) & 0xFFFF;
            break;
        case 0x60: //Increment	INC	0110RRRR	-	register
            op1 = Utils::Convert::register2int(instr.operandLeft);
            instr.code = (0x60 | op1) & 0xFF;
            break;
        case 0x7000: //Increment and Skip	ISZ	0111RRRR	AAAAAAAA	register, address
            op1 = Utils::Convert::register2int(instr.operandLeft);
            op2 = Utils::Convert::address2int(instr.operandRight);
            instr.code = ((0x7000 | (op1 << 8)) | Utils::Convert::to8bit(op2)) & 0xFFFF;
            break;
        case 0x80: //Add	ADD	1000RRRR	-	register
            op1 = Utils::Convert::register2int(instr.operandLeft);
            instr.code = (0x80 | op1) & 0xFF;
            break;
        case 0x90: //Subtract	SUB	1001RRRR	-	register
            op1 = Utils::Convert::register2int(instr.operandLeft);
            instr.code = (0x90 | op1) & 0xFF;
            break;
        case 0xA0: //Load	LD	1010RRRR	-	register
            op1 = Utils::Convert::register2int(instr.operandLeft);
            instr.code = (0xA0 | op1) & 0xFF;
            break;
        case 0xB0: //Exchange	XCH	1011RRRR	-	register
            op1 = Utils::Convert::register2int(instr.operandLeft);
            instr.code = (0xB0 | op1) & 0xFF;
            break;
        case 0xC0: //Branch Back and Load	BBL	1100DDDD	-	data
            op1 = Utils::Convert::dec2int(instr.operandLeft);
            instr.code = (0xC0 | Utils::Convert::to4bit(op1)) & 0xFF;
            break;
        case 0xD0: //Load Immediate	LDM	1101DDDD	-	data
            op1 = Utils::Convert::dec2int(instr.operandLeft);
            instr.code = (0xD0 | Utils::Convert::to4bit(op1)) & 0xFF;
            break;
        case 0xE0: //Write Main Memory	WRM	11100000	-	none
            instr.code = 0xE0;
            break;
        case 0xE1: //Write RAM Port	WMP	11100001	-	none
            instr.code = 0xE1;
            break;
        case 0xE2: //Write ROM Port	WRR	11100010	-	none
            instr.code = 0xE2;
            break;
        case 0xE4: //Write Status Char 0	WR0	11100100	-	none
            instr.code = 0xE4;
            break;
        case 0xE5: //Write Status Char 1	WR1	11100101	-	none
            instr.code = 0xE5;
            break;
        case 0xE6: //Write Status Char 2	WR2	11100110	-	none
            instr.code = 0xE6;
            break;
        case 0xE7: //Write Status Char 3	WR3	11100111	-	none
            instr.code = 0xE7;
            break;
        case 0xE8: //Subtract Main Memory	SBM	11101000	-	none
            instr.code = 0xE8;
            break;
        case 0xE9: //Read Main Memory	RDM	11101001	-	none
            instr.code = 0xE9;
            break;
        case 0xEA: //Read ROM Port	RDR	11101010	-	none
            instr.code = 0xEA;
            break;
        case 0xEB: //Add Main Memory	ADM	11101011	-	none
            instr.code = 0xEB;
            break;
        case 0xEC: //Read Status Char 0	RD0	11101100	-	none
            instr.code = 0xEC;
            break;
        case 0xED: //Read Status Char 1	RD1	11101101	-	none
            instr.code = 0xED;
            break;
        case 0xEE: //Read Status Char 2	RD2	11101110	-	none
            instr.code = 0xEE;
            break;
        case 0xEF: //Read Status Char 3	RD3	11101111	-	none
            instr.code = 0xEF;
            break;
        case 0xF0: //Clear Both	CLB	11110000	-	none
            instr.code = 0xF0;
            break;
        case 0xF1: //Clear Carry	CLC	11110001	-	none
            instr.code = 0xF1;
            break;
        case 0xF2: //Increment Accumulator	IAC	11110010	-	none
            instr.code = 0xF2;
            break;
        case 0xF3: //Complement Carry	CMC	11110011	-	none
            instr.code = 0xF3;
            break;
        case 0xF4: //Complement	CMA	11110100	-	none
            instr.code = 0xF4;
            break;
        case 0xF5: //Rotate Left	RAL	11110101	-	none
            instr.code = 0xF5;
            break;
        case 0xF6: //Rotate Right	RAR	11110110	-	none
            instr.code = 0xF6;
            break;
        case 0xF7: //Transfer Carry and Clear	TCC	11110111	-	none
            instr.code = 0xF7;
            break;
        case 0xF8: //Decrement Accumulator	DAC	11111000	-	none
            instr.code = 0xF8;
            break;
        case 0xF9: //Transfer Carry Subtract	TCS	11111001	-	none
            instr.code = 0xF9;
            break;
        case 0xFA: //Set Carry	STC	11111010	-	none
            instr.code = 0xFA;
            break;
        case 0xFB: //Decimal Adjust Accumulator	DAA	11111011	-	none
            instr.code = 0xFB;
            break;
        case 0xFC: //Keyboard Process	KBP	11111100	-	none
            instr.code = 0xFC;
            break;
        case 0xFD: //Designate Command Line	DCL	11111101	-	none
            instr.code = 0xFD;
            break;
        }

    }	// for
}

void Compiler::checkNoOperands(const Instruct& instr)
{
    if (instr.operandLeft != "" || instr.operandRight != "")
    {
        // write error
        //        stringstream s;
        //        s << "Error at line " << instr.lineNumber << ": Doesn't expect operands. Line: " << instr.line << endl;
        //        errList->addItem(QString::fromStdString(s.str()));
        errors.push_back( { instr.lineNumber,  "Doesn't expect operands.", instr.line} );
    }
}

void Compiler::checkNoRightOperand(const Instruct& instr)
{
    if (instr.operandRight != "")
    {
        // write error
        //        stringstream s;
        //        s << "Error at line " << instr.lineNumber << ": Doesn't expect right operand. Line: " << instr.line << endl;
        //        errList->addItem(QString::fromStdString(s.str()));
        errors.push_back( { instr.lineNumber,  "Doesn't expect right operand.", instr.line} );
    }
}

void Compiler::checkLeftOperandPair(const Instruct& instr)
{
    /*
     *  Check left operand
     *  it can be:
     *  - Pair
     */
    if (Instruction::Operand::isPair(instr.operandLeft))
    {
        // Ok, Nothing to do
    }
    else
    {
        // write error
        //        stringstream s;
        //        s << "Error at line " << instr.lineNumber << ": Bad format of left operand. Pair expected. Line: "
        //                << instr.line << endl;
        //        errList->addItem(QString::fromStdString(s.str()));
        errors.push_back( { instr.lineNumber,  "Bad format of left operand. Pair expected.", instr.line} );
    }
}

void Compiler::checkLeftOperandRegister(const Instruct& instr)
{
    /*
     *  Check left operand
     *  it can be:
     *  - Register
     */
    if (Instruction::Operand::isRegister(instr.operandLeft))
    {
        // Ok, Nothing to do
    }
    else
    {

        // write error
        //        stringstream s;
        //        s << "Error at line " << instr.lineNumber << ": Bad format of left operand. Register expected. Line: "
        //                << instr.line << endl;
        //        errList->addItem(QString::fromStdString(s.str()));
        errors.push_back( { instr.lineNumber,  "Bad format of left operand. Register expected.", instr.line} );
    }
}

void Compiler::checkLeftOperandCondition(Instruct& instr)
{
    /*
     *  Check left operand
     *  It can be:
     *  - Number
     *    - Bin
     *    - Hex
     *    - Dec
     *  - Label
     *  - Expression
     *
     *  If else it should throw an error to the error stream
     */
    if (Utils::Number::isNumber(instr.operandLeft))
    {
        // Ok, Nothing to do
    }
    else if (Instruction::Operand::isLabel(instr.operandLeft))
    {
        std::string c = getConstByLabel(instr.operandLeft);
        if (c != "")
        {
            instr.operandLeft = c;
        }
        else
        {
            // write error
            //            stringstream s;
            //            s << "Error at line " << instr.lineNumber << ": Unknown constant " << instr.name << " . Line: "
            //                    << instr.line << endl;
            //            errList->addItem(QString::fromStdString(s.str()));
            errors.push_back( { instr.lineNumber,  "Unknown constant \"" + instr.name + "\".", instr.line} );
        }
    }
    else if (Instruction::Operand::isMathExpression(instr.operandLeft))
    {
        // TODO Value Expression
    }
    else
    {
        // write error
        //        stringstream s;
        //        s << "Error at line " << instr.lineNumber << ": Bad format of left operand. Line: " << instr.line << endl;
        //        errList->addItem(QString::fromStdString(s.str()));
        errors.push_back( { instr.lineNumber,  "Bad format of left operand.", instr.line} );
    }
}

void Compiler::checkRightOperandAddress(Instruct& instr)
{
    /*
     * Check right operand
     * It can be:
     * - Number
     *   - Bin
     *   - Hex
     *   - Dec
     * - Label
     * - Expression
     */

    if (Utils::Number::isNumber(instr.operandRight))
    {
        // Ok, Nothing to do
    }
    else if (Instruction::Operand::isLabel(instr.operandRight))
    {
        int c = getAddressByLabel(instr.operandRight);
        if (c != -1)
        {
            instr.operandRight = std::to_string(c);
        }
        else
        {
            // write error
            //            stringstream s;
            //            s << "Error at line " << instr.lineNumber << ": Unknown label. Line: " << instr.line << endl;
            //            errList->addItem(QString::fromStdString(s.str()));
            errors.push_back( { instr.lineNumber,  "Unknown label.", instr.line} );
        }
    }
    else if (Instruction::Operand::isMathExpression(instr.operandRight))
    {
        // TODO Value Expression
    }
    else
    {
        // write error
        //        stringstream s;
        //        s << "Error at line " << instr.lineNumber << ": Bad format of right operand. Line: " << instr.line << endl;
        //        errList->addItem(QString::fromStdString(s.str()));
        errors.push_back( { instr.lineNumber,  "Bad format of right operand.", instr.line} );
    }
}

void Compiler::checkLeftOperandData(Instruct& instr)
{
    /*
     *  Check right operand
     *  it can be:
     *  - Number
     *    - Bin
     *    - Hex
     *    - Dec
     *  - Label (Const)
     */

    if (Utils::Number::isNumber(instr.operandLeft))
    {
        // Ok, Nothing to do
    }
    else if (Instruction::Operand::isLabel(instr.operandLeft))
    {
        std::string c = getConstByLabel(instr.operandLeft);
        if (c != "")
        {
            instr.operandLeft = c;
        }
        else
        {
            // write error
            //            stringstream s;
            //            s << "Error at line " << instr.lineNumber << ": Unknown constant " << instr.name << " . Line: "
            //                    << instr.line << endl;
            //            errList->addItem(QString::fromStdString(s.str()));
            errors.push_back( { instr.lineNumber,  "Unknown constant \"" + instr.name + "\".", instr.line} );
        }
    }
    else if (Instruction::Operand::isMathExpression(instr.operandLeft))
    {
        // TODO Evaluate expression
    }
    else
    {
        // write error
        //        stringstream s;
        //        s << "Error at line " << instr.lineNumber << ": Bad format of left operand. Line: " << instr.line << endl;
        //        errList->addItem(QString::fromStdString(s.str()));
        errors.push_back( { instr.lineNumber,  "Bad format of left operand.", instr.line} );
    }
}

void Compiler::checkRightOperandData(Instruct& instr)
{
    /*
     *  Check right operand
     *  it can be:
     *  - Number
     *    - Bin
     *    - Hex
     *    - Dec
     *  - Label (Const)
     */

    if (Utils::Number::isNumber(instr.operandRight))
    {
        // Ok, Nothing to do
    }
    else if (Instruction::Operand::isLabel(instr.operandRight))
    {
        std::string c = getConstByLabel(instr.operandRight);
        if (c != "")
        {
            instr.operandRight = c;
        }
        else
        {
            // write error
            //            stringstream s;
            //            s << "Error at line " << instr.lineNumber << ": Unknown constant " << instr.name << " . Line: "
            //                    << instr.line << endl;
            //            errList->addItem(QString::fromStdString(s.str()));
            errors.push_back( { instr.lineNumber,  "Unknown constant \"" + instr.name + "\".", instr.line} );
        }
    }
    else if (Instruction::Operand::isMathExpression(instr.operandRight))
    {
        // TODO Evaluate expression
        std::cout << instr.operandRight << std::endl;
    }
    else
    {
        // write error
        //        stringstream s;
        //        s << "Error at line " << instr.lineNumber << ": Bad format of right operand. Line: " << instr.line << endl;
        //        errList->addItem(QString::fromStdString(s.str()));
        errors.push_back( { instr.lineNumber,  "Bad format of right operand.", instr.line} );
    }
}

void Compiler::checkLeftOperandAddress(Instruct& instr)
{
    /*
     * Check left operand
     * It can be:
     * - Number
     *   - Bin
     *   - Hex
     *   - Dec
     * - Label
     * - Expression
     */

    if (Utils::Number::isNumber(instr.operandLeft))
    {
        // Ok, Nothing to do
    }
    else if (Instruction::Operand::isLabel(instr.operandLeft))
    {
        int c = getAddressByLabel(instr.operandLeft);
        if (c != -1)
        {
            instr.operandLeft = std::to_string(c);
        }
        else
        {
            // write error
            //            stringstream s;
            //            s << "Error at line " << instr.lineNumber << ": Unknown label. Line: " << instr.line << endl;
            //            errList->addItem(QString::fromStdString(s.str()));
            errors.push_back( { instr.lineNumber,  "Unknown label.", instr.line} );
        }
    }
    else if (Instruction::Operand::isMathExpression(instr.operandLeft))
    {
        // TODO Value Expression
    }
    else
    {
        // write error
        //        stringstream s;
        //        s << "Error at line " << instr.lineNumber << ": Bad format of left operand. Line: " << instr.line << endl;
        //        errList->addItem(QString::fromStdString(s.str()));
        errors.push_back( { instr.lineNumber,  "Bad format of left operand.", instr.line} );
    }
}

void Compiler::toCompile()
{
    int address = 0; // Address of the current line (command)
    int lineNumber = 0;

    /*
     * First passing
     * Parsing and saving to tables
     */

    for (std::string& line : code)  // TODO Maybe line is const ??
    {
        std::string currentLine = line;

        std::string label;
        std::string instruction;
        std::string operand;
        std::string operandLeft;
        std::string operandRight;

        lineNumber++;

        parseLine(line, label, instruction, operand, operandLeft, operandRight, lineNumber);

        saveToTables(currentLine, label, instruction, operandLeft, operandRight, lineNumber, address);

        address += Instruction::CommandSet::getLength(instruction);

    } // for

    /*
     * Second passing
     * Preprocessor
     *
     * TODO Replace labels with addresses and constants
     * TODO Counting operands
     * Check errors
     */
    preprocessing();

    /*
     * Composing
     */
    composing();

    //	for (const instruction& i : instructionTable) {
    //		cout << std::hex << i.code << " " << i.name << " " << i.operandLeft << " " << i.operandRight << endl;
    //	}

    /*
     * Make a file with an object code
     */
    outputfile.open(output, ios::binary | ios::out);

    if (outputfile.is_open())
    {
        for (const Instruct& i : instructionTable)
        {
            if (i.code & 0xFF00)
            {
                outputfile << (char) ((i.code & 0xFF00) >> 8);
            }

            outputfile << (char) (i.code & 0xFF);

        }

        outputfile.close();
    }
    else
    {
        throw "File was not created";
    }

}// toCompile

vector<Error> Compiler::getErrors() const
{
    return errors;
}

vector<unsigned int> Compiler::getCompiledCode() const
{
    std::vector<unsigned int> compiledCode;

    for (const Instruct& ins : instructionTable)
    {
        compiledCode.push_back(ins.code);
    }

    return compiledCode;
}


