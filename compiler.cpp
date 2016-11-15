/*
 * SourceCode.cpp
 *
 *  Created on: 16. 8. 2016
 *      Author: user
 */

#include "Compiler.h"

// TODO ??? maybe make switcher to BigEndian or LittleEndian
// TODO Error Stream
// TODO Maybe to do Error Class
// TODO toCompile method divide to several methods
// TODO Checking Labels. They can't be the same as the names of the instructions, registers, pairs and other keywords
// TODO Format of a pair maybe P0, p0 and 0P, 0p. Maybe to do 0P and 0p format too.
// TODO Format of a register maybe R0, r0 and 0R, 0r. Maybe to do 0R and 0r format too.

string Compiler::trimStrong(const string& text) {
    return regex_replace(text, regex("([[:space:]]{1})"), "");
}

string Compiler::trim(const string& text) {

	string res = regex_replace(text, regex("([[:space:]]+)"), " ");
	if (res.empty() || strcmp(res.c_str(), " ") == 0) {
		return "";
	}

	if (res.at(0) == ' ') {
		res.erase(0, 1);
	}

	if (res.at(res.length() - 1) == ' ') {
		res.erase(res.length() - 1, 1);
	}

	return res;
}

string Compiler::getConstByLabel(const string& label) {
	for (constants c : constantsTable) {
		if (label == c.label) {
			if (regex_match(c.constant, rOpDec) || regex_match(c.constant, rOpBin) || regex_match(c.constant, rOpHex)) {
				return c.constant;
			} else if (regex_match(c.constant, rOpLabel) && !c.constant.empty()) {
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

int Compiler::getInstructionLength(const string& name) {
	for (instruction_set instr : set) {
		if (instr.mnemonic == name) {
			return (instr.code & 0xFF00) ? 2 : 1;
		}
	}

	return 0;
}

int Compiler::getAddressByLabel(const string& label) {
	for (labels l : labelsTable) {
		if (l.label == label) {
			return l.address;
		}
	}

	return -1;
}

bool Compiler::checkLabelExist(const string& label) {
	for (labels l : labelsTable) {
		if (label == l.label) {
			return true;
		}
	}

	for (constants c : constantsTable) {
		if (label == c.label) {
			return true;
		}
	}

	return false;
}

int Compiler::getCodeByInstruction(const string& instr) {
	for (const instruction_set& i : set) {
		if (instr == i.mnemonic) {
			return i.code;
		}
	}

	return -1;
}

bool Compiler::isInstruction(const string& name) const {
	for (instruction_set i : set) {
		if (i.mnemonic == name) {
			return true;
		}
	}

	return false;
}

void Compiler::saveToTables(const string& line, const string& label, const string& instruction,
		const string& operandLeft, const string& operandRight, const int& lineNumber, const int& address) {
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

	if (label == "" && instruction == "" && operandLeft == "" && operandRight == "") {
		/*
		 * Case 0
		 * If line is empty, then nothing to do
		 */
	} else if (label == "" && instruction == "" && operandLeft == "" && operandRight != "") {
		/*
		 *	Case 1
		 */

        // write error
//        stringstream s;
//        s << "Error at line " << lineNumber << ": Instruction expected, but left operand was acquired (1). Line: "
//                << trim(line) << endl;
//        errList->addItem(QString::fromStdString(s.str()));
        errors.push_back( { lineNumber,  "Instruction expected, but left operand was acquired (1).", trim(line)} );
	} else if (label == "" && instruction == "" && operandLeft != "" && operandRight == "") {
		/*
		 *	Case 2
		 */

        // write error
//        stringstream s;
//        s << "Error at line " << lineNumber << ": Instruction expected, but right operand was acquired (2). Line: "
//                << trim(line) << endl;
//        errList->addItem(QString::fromStdString(s.str()));
        errors.push_back( { lineNumber,  "Instruction expected, but right operand was acquired (2).", trim(line)} );
	} else if (label == "" && instruction == "" && operandLeft != "" && operandRight != "") {
		/*
		 *	Case 3
		 */

        // write error
//        stringstream s;
//        s << "Error at line " << lineNumber << ": Instruction expected, but both operands was acquired (3). Line: "
//                << trim(line) << endl; // TODO Delete this cout
//        errList->addItem(QString::fromStdString(s.str()));
        errors.push_back( { lineNumber,  "Instruction expected, but both operands was acquired (3).", trim(line)} );
	} else if (label == "" && instruction != "" && operandLeft == "" && operandRight == "") {
		/*
		 *	Case 4
		 * 	if a line has only instruction and no label
		 *	For example:
		 *	WR0
		 * 	So it only writes the command to the instructionTable
		 */

        instructionTable.push_back( { instruction, operandLeft, operandRight, trim(line), lineNumber, -1 });
	} else if (label == "" && instruction != "" && operandLeft == "" && operandRight != "") {
		/*
		 *	Case 5
		 *	ERROR, Must be LeftOperand
		 */

        // write error
//        stringstream s;
//        s << "Error at line " << lineNumber << ": Left operand acquired (5). Line: " << trim(line) << endl;
//        errList->addItem(QString::fromStdString(s.str()));
        errors.push_back( { lineNumber,  "Left operand acquired (5).", trim(line)} );
	} else if (label == "" && instruction != "" && operandLeft != "" && operandRight == "") {
		/*
		 *	Case 6
		 * 	if a line has only instruction and no label
		 *	For example:
		 * 	JUN 30
		 * 	So it only writes the command to the instructionTable
		 */

        instructionTable.push_back( { instruction, operandLeft, operandRight, trim(line), lineNumber, -1 });
	} else if (label == "" && instruction != "" && operandLeft != "" && operandRight != "") {
		/*
		 *	Case 7
		 * 	if a line has only instruction and no label
		 *	For example:
		 * 	FIM P1, 45
		 * 	So it only writes the command to the instructionTable
		 */

        instructionTable.push_back( { instruction, operandLeft, operandRight, trim(line), lineNumber, -1 });
	} else if (label != "" && instruction == "" && operandLeft == "" && operandRight == "") {
		/*
		 *	Case 8
		 */

        // write error
//        stringstream s;
//        s << "Error at line " << lineNumber << ": Label to an empty line (8). Line: " << trim(line) << endl;
//        errList->addItem(QString::fromStdString(s.str()));
        errors.push_back( { lineNumber,  "Label to an empty line (8).", trim(line)} );
	} else if (label != "" && instruction == "" && operandLeft == "" && operandRight != "") {
		/*
		 *	Case 9
		 */

        // write error
//        stringstream s;
//        s << "Error at line " << lineNumber << ": Label to right operand (9). Line: " << trim(line) << endl;
//        errList->addItem(QString::fromStdString(s.str()));
        errors.push_back( { lineNumber,  "Label to right operand (9).", trim(line)} );
	} else if (label != "" && instruction == "" && operandLeft != "" && operandRight == "") {
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
	} else if (label != "" && instruction == "" && operandLeft != "" && operandRight != "") {
		/*
		 *	Case B
		 */

        // write error
//        stringstream s;
//        s << "Error at line " << lineNumber << ": Label to both operands (B). Line: " << trim(line) << endl;
//        errList->addItem(QString::fromStdString(s.str()));
        errors.push_back( { lineNumber,  "Label to both operands (B).", trim(line)} );
	} else if (label != "" && instruction != "" && operandLeft == "" && operandRight == "") {
		/*
		 *	Case C
		 *	if a line has a label
		 *	Label, Instruction Operand
		 *	For example:
		 *	AAA, WR0
		 *	So label consider an address
		 */

		labelsTable.push_back( { label, address });
        instructionTable.push_back( { instruction, operandLeft, operandRight, trim(line), lineNumber, -1 });
	} else if (label != "" && instruction != "" && operandLeft == "" && operandRight != "") {
		/*
		 * Case D
		 * ERROR, Must be LeftOperand
		 */

        // write error
//        stringstream s;
//        s << "Error at line " << lineNumber << ": Expected left operand (D). Line: " << trim(line) << endl;
//        errList->addItem(QString::fromStdString(s.str()));
        errors.push_back( { lineNumber,  "Expected left operand (D).", trim(line)} );
	} else if (label != "" && instruction != "" && operandLeft != "" && operandRight == "") {
		/*
		 *	Case E
		 *	if a line has a label
		 *	Label, Instruction Operand
		 *	For example:
		 *	ABC, JUN 20H
		 *	So label consider an address
		 */

		labelsTable.push_back( { label, address });
        instructionTable.push_back( { instruction, operandLeft, operandRight, trim(line), lineNumber, -1 });
	} else if (label != "" && instruction != "" && operandLeft != "" && operandRight != "") {
		/*
		 *	Case F
		 *	if a line has a label
		 *	Label, Instruction Operand
		 *	For example:
		 *	BBC, FIM P0, 50
		 *	So label consider an address
		 */

		labelsTable.push_back( { label, address });
        instructionTable.push_back( { instruction, operandLeft, operandRight, trim(line), lineNumber, -1 });
	} else {
		/*
		 *  TODO write an error to ErrorStream
		 *  Here is some unexpected error
		 */

        // write error
//        stringstream s;
//        s << "Error at line " << lineNumber << ": Unexpected error. Line: " << trim(line) << endl;
//        errList->addItem(QString::fromStdString(s.str()));
        errors.push_back( { lineNumber,  "Unexpected error.", trim(line)} );
	}
}

void Compiler::parseLine(string& line, string& label, string& instruction, string& operand, string& operandLeft,
		string& operandRight, const int& lineNumber) {

	string currentLine = trim(line);
	smatch m;
	// Find and delete from line a comment, if it exists
	if (regex_search(line, m, rComment)) {
		line = m.prefix().str();	// We don't need a comment in ObjectCode, so only delete it
	}

	// Parse a label
	if (regex_search(line, m, rLabel)) {
		label = trimStrong(m[0]);	// A label on a line
		label = regex_replace(label, regex("(,)"), "");	// Delete "," from label
		line = m.suffix().str();

		string prefix = m.prefix().str();
		// Check if something is by left side of a label. If it is, then this is error
		if (!trimStrong(prefix).empty()) {

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
		if (checkLabelExist(label)) {

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
	if (regex_search(line, m, rOpExpr) && !isInstruction(m[0])) {
		operandLeft = trimStrong(m[0]);
		return;
	}

	// Parse an instruction
	if (regex_search(line, m, rInstruction)) {
		instruction = trimStrong(m[0]);	// An instruction on a line
		line = m.suffix().str();
	}

	// Parse operand(s)
	if (regex_search(line, m, rOperand)) {
		operand = m[0];	//	Operand
		line = m.suffix().str();

		// Divide operand to left and right, if they exist
		operandLeft = trimStrong(operand);
		if (regex_search(operand, m, regex("(,)"))) {
			operandLeft = trimStrong(m.prefix().str());
			operandRight = trimStrong(m.suffix().str());
		}
	}

	/*
	 * If line is not empty, that means, that compiler couldn't resolve something,
	 * so we should to throw an error to the error stream
	 */
	if (!trimStrong(line).empty()) {

        // write error
//        stringstream s;
//        s << "Error at line " << lineNumber << ". Can't resolve " << line << ". Line: " << currentLine << endl;
//        errList->addItem(QString::fromStdString(s.str()));
        errors.push_back( { lineNumber,  "Can't resolve \"" + line + "\".", currentLine} );
	}
}

void Compiler::preprocessing() {

	// Evaluate constant labels
	for (constants& c : constantsTable) {
		if (regex_match(c.constant, rOpLabel)) {
			c.constant = getConstByLabel(c.constant);
		}
	}

//	for (constants& c : constantsTable) {
//		cout << c.label << " " << c.constant << endl;
//	}

    for (Instruction& instr : instructionTable) {
		/*
		 * Check instructions
		 * if don't exist or if they have got wrong operands
		 */
		switch (getCodeByInstruction(instr.name)) {
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

void Compiler::composing() {
    for (Instruction& instr : instructionTable) {
		int op1 = 0;
		int op2 = 0;
		/*
		 * Compose instructions to object code
		 */
		switch (getCodeByInstruction(instr.name)) {
		case 0x0:
			instr.code = 0x0;
			break;
		case 0x1000: // Jump Conditional	JCN	0001CCCC	AAAAAAAA	condition, address
			op1 = condition2int(instr.operandLeft);
			op2 = address2int(instr.operandRight);
			instr.code = ((0x1000 | (to4bit(op1) << 8)) | to8bit(op2)) & 0xFFFF;
			break;
		case 0x2000: //Fetch Immediate	FIM	0010RRR0	DDDDDDDD	register pair, data
			op1 = pair2int(instr.operandLeft);
			op2 = dec2int(instr.operandRight);
			instr.code = ((0x2000 | (op1 << 9)) | to8bit(op2)) & 0xFFFF;
			break;
		case 0x21: //Send Register Control	SRC	0010RRR1	-	register pair
			op1 = pair2int(instr.operandLeft);
			instr.code = (0x21 | (op1 << 1)) & 0xFF;
			break;
		case 0x30: //Fetch Indirect	FIN	0011RRR0	-	register pair
			op1 = pair2int(instr.operandLeft);
			instr.code = (0x30 | (op1 << 1)) & 0xFF;
			break;
		case 0x31: //Jump Indirect	JIN	0011RRR1	-	register pair
			op1 = pair2int(instr.operandLeft);
			instr.code = (0x31 | (op1 << 1)) & 0xFF;
			break;
		case 0x4000: //Jump Unconditional	JUN	0100AAAA	AAAAAAAA	address
			op1 = address2int(instr.operandLeft);
			instr.code = (0x4000 | to12bit(op1)) & 0xFFFF;
			break;
		case 0x5000: //Jump to Subroutine	JMS	0101AAAA	AAAAAAAA	address
			op1 = address2int(instr.operandLeft);
			instr.code = (0x5000 | to12bit(op1)) & 0xFFFF;
			break;
		case 0x60: //Increment	INC	0110RRRR	-	register
			op1 = register2int(instr.operandLeft);
			instr.code = (0x60 | op1) & 0xFF;
			break;
		case 0x7000: //Increment and Skip	ISZ	0111RRRR	AAAAAAAA	register, address
			op1 = register2int(instr.operandLeft);
			op2 = address2int(instr.operandRight);
			instr.code = ((0x7000 | (op1 << 8)) | to8bit(op2)) & 0xFFFF;
			break;
		case 0x80: //Add	ADD	1000RRRR	-	register
			op1 = register2int(instr.operandLeft);
			instr.code = (0x80 | op1) & 0xFF;
			break;
		case 0x90: //Subtract	SUB	1001RRRR	-	register
			op1 = register2int(instr.operandLeft);
			instr.code = (0x90 | op1) & 0xFF;
			break;
		case 0xA0: //Load	LD	1010RRRR	-	register
			op1 = register2int(instr.operandLeft);
			instr.code = (0xA0 | op1) & 0xFF;
			break;
		case 0xB0: //Exchange	XCH	1011RRRR	-	register
			op1 = register2int(instr.operandLeft);
			instr.code = (0xB0 | op1) & 0xFF;
			break;
		case 0xC0: //Branch Back and Load	BBL	1100DDDD	-	data
			op1 = dec2int(instr.operandLeft);
			instr.code = (0xC0 | to4bit(op1)) & 0xFF;
			break;
		case 0xD0: //Load Immediate	LDM	1101DDDD	-	data
			op1 = dec2int(instr.operandLeft);
			instr.code = (0xD0 | to4bit(op1)) & 0xFF;
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

void Compiler::checkNoOperands(const Instruction& instr) {
	if (instr.operandLeft != "" || instr.operandRight != "") {
        // write error
//        stringstream s;
//        s << "Error at line " << instr.lineNumber << ": Doesn't expect operands. Line: " << instr.line << endl;
//        errList->addItem(QString::fromStdString(s.str()));
        errors.push_back( { instr.lineNumber,  "Doesn't expect operands.", instr.line} );
	}
}

void Compiler::checkNoRightOperand(const Instruction& instr) {
	if (instr.operandRight != "") {
        // write error
//        stringstream s;
//        s << "Error at line " << instr.lineNumber << ": Doesn't expect right operand. Line: " << instr.line << endl;
//        errList->addItem(QString::fromStdString(s.str()));
        errors.push_back( { instr.lineNumber,  "Doesn't expect right operand.", instr.line} );
	}
}

void Compiler::checkLeftOperandPair(const Instruction& instr) {
	/*
	 *  Check left operand
	 *  it can be:
	 *  - Pair
	 */
	if (regex_match(instr.operandLeft, rOpPair)) {
		// Ok, Nothing to do
	} else {
        // write error
//        stringstream s;
//        s << "Error at line " << instr.lineNumber << ": Bad format of left operand. Pair expected. Line: "
//                << instr.line << endl;
//        errList->addItem(QString::fromStdString(s.str()));
        errors.push_back( { instr.lineNumber,  "Bad format of left operand. Pair expected.", instr.line} );
	}
}

void Compiler::checkLeftOperandRegister(const Instruction& instr) {
	/*
	 *  Check left operand
	 *  it can be:
	 *  - Pair
	 */
	if (regex_match(instr.operandLeft, rOpRegister)) {
		// Ok, Nothing to do
	} else {

        // write error
//        stringstream s;
//        s << "Error at line " << instr.lineNumber << ": Bad format of left operand. Register expected. Line: "
//                << instr.line << endl;
//        errList->addItem(QString::fromStdString(s.str()));
        errors.push_back( { instr.lineNumber,  "Bad format of left operand. Register expected.", instr.line} );
	}
}

void Compiler::checkLeftOperandCondition(Instruction& instr) {
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
	if (regex_match(instr.operandLeft, rOpBin) || regex_match(instr.operandLeft, rOpHex)
			|| regex_match(instr.operandLeft, rOpDec)) {
		// Ok, Nothing to do
	} else if (regex_match(instr.operandLeft, rOpLabel)) {
		string c = getConstByLabel(instr.operandLeft);
		if (c != "") {
			instr.operandLeft = c;
		} else {
            // write error
//            stringstream s;
//            s << "Error at line " << instr.lineNumber << ": Unknown constant " << instr.name << " . Line: "
//                    << instr.line << endl;
//            errList->addItem(QString::fromStdString(s.str()));
            errors.push_back( { instr.lineNumber,  "Unknown constant \"" + instr.name + "\".", instr.line} );
		}
	} else if (regex_match(instr.operandLeft, rOpExpr)) {
		// TODO Value Expression
	} else {
        // write error
//        stringstream s;
//        s << "Error at line " << instr.lineNumber << ": Bad format of left operand. Line: " << instr.line << endl;
//        errList->addItem(QString::fromStdString(s.str()));
        errors.push_back( { instr.lineNumber,  "Bad format of left operand.", instr.line} );
	}
}

void Compiler::checkRightOperandAddress(Instruction& instr) {
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

	if (regex_match(instr.operandRight, rOpBin) || regex_match(instr.operandRight, rOpHex)
			|| regex_match(instr.operandRight, rOpDec)) {
		// Ok, Nothing to do
	} else if (regex_match(instr.operandRight, rOpLabel)) {
		int c = getAddressByLabel(instr.operandRight);
		if (c != -1) {
			instr.operandRight = std::to_string(c);
		} else {
            // write error
//            stringstream s;
//            s << "Error at line " << instr.lineNumber << ": Unknown label. Line: " << instr.line << endl;
//            errList->addItem(QString::fromStdString(s.str()));
            errors.push_back( { instr.lineNumber,  "Unknown label.", instr.line} );
		}
	} else if (regex_match(instr.operandRight, rOpExpr)) {
		// TODO Value Expression
	} else {
        // write error
//        stringstream s;
//        s << "Error at line " << instr.lineNumber << ": Bad format of right operand. Line: " << instr.line << endl;
//        errList->addItem(QString::fromStdString(s.str()));
        errors.push_back( { instr.lineNumber,  "Bad format of right operand.", instr.line} );
	}
}
void Compiler::checkLeftOperandData(Instruction& instr) {
	/*
	 *  Check right operand
	 *  it can be:
	 *  - Number
	 *    - Bin
	 *    - Hex
	 *    - Dec
	 *  - Label (Const)
	 */

	if (regex_match(instr.operandLeft, rOpBin) || regex_match(instr.operandLeft, rOpHex)
			|| regex_match(instr.operandLeft, rOpDec)) {
		// Ok, Nothing to do
	} else if (regex_match(instr.operandLeft, rOpLabel)) {
		string c = getConstByLabel(instr.operandLeft);
		if (c != "") {
			instr.operandLeft = c;
		} else {
            // write error
//            stringstream s;
//            s << "Error at line " << instr.lineNumber << ": Unknown constant " << instr.name << " . Line: "
//                    << instr.line << endl;
//            errList->addItem(QString::fromStdString(s.str()));
            errors.push_back( { instr.lineNumber,  "Unknown constant \"" + instr.name + "\".", instr.line} );
		}
	} else if (regex_match(instr.operandLeft, rOpExpr)) {
		// TODO Evaluate expression
	} else {
        // write error
//        stringstream s;
//        s << "Error at line " << instr.lineNumber << ": Bad format of left operand. Line: " << instr.line << endl;
//        errList->addItem(QString::fromStdString(s.str()));
        errors.push_back( { instr.lineNumber,  "Bad format of left operand.", instr.line} );
	}
}

void Compiler::checkRightOperandData(Instruction& instr) {
	/*
	 *  Check right operand
	 *  it can be:
	 *  - Number
	 *    - Bin
	 *    - Hex
	 *    - Dec
	 *  - Label (Const)
	 */

	if (regex_match(instr.operandRight, rOpBin) || regex_match(instr.operandRight, rOpHex)
			|| regex_match(instr.operandRight, rOpDec)) {
		// Ok, Nothing to do
	} else if (regex_match(instr.operandRight, rOpLabel)) {
		string c = getConstByLabel(instr.operandRight);
		if (c != "") {
			instr.operandRight = c;
		} else {
            // write error
//            stringstream s;
//            s << "Error at line " << instr.lineNumber << ": Unknown constant " << instr.name << " . Line: "
//                    << instr.line << endl;
//            errList->addItem(QString::fromStdString(s.str()));
            errors.push_back( { instr.lineNumber,  "Unknown constant \"" + instr.name + "\".", instr.line} );
		}
	} else if (regex_match(instr.operandRight, rOpExpr)) {
		// TODO Evaluate expression
	} else {
        // write error
//        stringstream s;
//        s << "Error at line " << instr.lineNumber << ": Bad format of right operand. Line: " << instr.line << endl;
//        errList->addItem(QString::fromStdString(s.str()));
        errors.push_back( { instr.lineNumber,  "Bad format of right operand.", instr.line} );
	}
}

void Compiler::checkLeftOperandAddress(Instruction& instr) {
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

	if (regex_match(instr.operandLeft, rOpBin) || regex_match(instr.operandLeft, rOpHex)
			|| regex_match(instr.operandLeft, rOpDec)) {
		// Ok, Nothing to do
	} else if (regex_match(instr.operandLeft, rOpLabel)) {
		int c = getAddressByLabel(instr.operandLeft);
		if (c != -1) {
			instr.operandLeft = std::to_string(c);
		} else {
            // write error
//            stringstream s;
//            s << "Error at line " << instr.lineNumber << ": Unknown label. Line: " << instr.line << endl;
//            errList->addItem(QString::fromStdString(s.str()));
            errors.push_back( { instr.lineNumber,  "Unknown label.", instr.line} );
		}
	} else if (regex_match(instr.operandLeft, rOpExpr)) {
		// TODO Value Expression
	} else {
        // write error
//        stringstream s;
//        s << "Error at line " << instr.lineNumber << ": Bad format of left operand. Line: " << instr.line << endl;
//        errList->addItem(QString::fromStdString(s.str()));
        errors.push_back( { instr.lineNumber,  "Bad format of left operand.", instr.line} );
	}
}

int Compiler::register2int(const string& name) const {
	string t = name;
    if (!t.empty() && regex_match(name, rOpRegister)) {
		t.erase(0, 1);

//		int n = stoi(t);
        int n = QString::fromStdString(t).toInt();

		return (n >= 0 && n <= 0xF) ? n : -1;
	}

	return -1;
}

int Compiler::pair2int(const string& name) const {
	string t = name;
    if (!t.empty() && regex_match(name, rOpPair)) {
		t.erase(0, 1);

//		int n = stoi(t);
        int n = QString::fromStdString(t).toInt();

		return (n >= 0 && n <= 7) ? n : -1;
	}

	return -1;
}

int Compiler::condition2int(const string& cond) const {
    if(cond.empty()) {
        return -1;
    }


//	return stoi(cond);
    return QString::fromStdString(cond).toInt();
}

int Compiler::address2int(const string& addr) const {
    if(addr.empty()) {
        return -1;
    }

//	return stoi(addr);
    return QString::fromStdString(addr).toInt();
}

int Compiler::dec2int(const string& dec) const {
    if (dec.empty()) {
        return -1;
    }

//	return stoi(dec);
    return QString::fromStdString(dec).toInt();
}

int Compiler::to4bit(const int& op) const {
	return (op % 0x10);
}

int Compiler::to8bit(const int& op) const {
	return (op % 0x100);
}

int Compiler::to12bit(const int& op) const {
	return (op % 0x1000);
}

int Compiler::to4bitStrong(const int& op) const {
	return (op & 0xF);
}

int Compiler::to8bitStrong(const int& op) const {
	return (op & 0xFF);
}

int Compiler::to12bitStrong(const int& op) const {
	return (op & 0xFFF);
}

Compiler::Compiler(const string& filename, const string& output) {

	this->output = output;

	// Templates
	rLabel = "[[:alpha:]][[:alnum:]]{2,}(,)";
	rInstruction = "[[:alpha:]]{2,}[[:alnum:]]?";
	rOperand = "([[:blank:]]+[[:print:]]+[[:blank:]]*)(,)?([[:blank:]]+[[:print:]]+[[:blank:]]*)?";
	rComment = "/[[:print:]]*";

	/*
	 *  rOpExpr not exact, always should be controlled on other regex.
     *  If it is not a pair, register, label and so on, only in this case we say, that it is a mathematical expression.
	 *  In other case we says, that it is not an expression
	 *  For example:
	 *  If rOpExpr equals true and other regex are false, we say that it is an expression.
	 *  If rOpExpr equals true and for example rOpPair is true, then rOpPair has greater priority and we say that it is a pair.
	 */
	rOpExpr = "([*]?[+-]?[[:alnum:]]+)+";
	rOpPair = "[Pp][0-7]";
	rOpRegister = "[Rr]([0-9]|(1[0-6]))";
	rOpHex = "([0-F]+H)|([0-f]+H)|([0-F]+h)|([0-f]+h)";
	rOpBin = "([01]+B)|([01]b)";
	rOpDec = "[0-9]+";
	rOpLabel = "[[:alpha:]][[:alnum:]]{2,}";

	set.push_back( { "NOP", 0x0 });
	set.push_back( { "JCN", 0x1000 });
	set.push_back( { "FIM", 0x2000 });
	set.push_back( { "SRC", 0x21 });
	set.push_back( { "FIN", 0x30 });
	set.push_back( { "JIN", 0x31 });
	set.push_back( { "JUN", 0x4000 });
	set.push_back( { "JMS", 0x5000 });
	set.push_back( { "INC", 0x60 });
	set.push_back( { "ISZ", 0x7000 });
	set.push_back( { "ADD", 0x80 });
	set.push_back( { "SUB", 0x90 });
	set.push_back( { "LD", 0xA0 });
	set.push_back( { "XCH", 0xB0 });
	set.push_back( { "BBL", 0xC0 });
	set.push_back( { "LDM", 0xD0 });
	set.push_back( { "WRM", 0xE0 });
	set.push_back( { "WMP", 0xE1 });
	set.push_back( { "WRR", 0xE2 });
	set.push_back( { "WR0", 0xE4 });
	set.push_back( { "WR1", 0xE5 });
	set.push_back( { "WR2", 0xE6 });
	set.push_back( { "WR3", 0xE7 });
	set.push_back( { "SBM", 0xE8 });
	set.push_back( { "RDM", 0xE9 });
	set.push_back( { "RDR", 0xEA });
	set.push_back( { "ADM", 0xEB });
	set.push_back( { "RD0", 0xEC });
	set.push_back( { "RD1", 0xED });
	set.push_back( { "RD2", 0xEE });
	set.push_back( { "RD3", 0xEF });
	set.push_back( { "CLB", 0xF0 });
	set.push_back( { "CLC", 0xF1 });
	set.push_back( { "IAC", 0xF2 });
	set.push_back( { "CMC", 0xF3 });
	set.push_back( { "CMA", 0xF4 });
	set.push_back( { "RAL", 0xF5 });
	set.push_back( { "RAR", 0xF6 });
	set.push_back( { "TCC", 0xF7 });
	set.push_back( { "DAC", 0xF8 });
	set.push_back( { "TCS", 0xF9 });
	set.push_back( { "STC", 0xFA });
	set.push_back( { "DAA", 0xFB });
	set.push_back( { "KBP", 0xFC });
	set.push_back( { "DCL", 0xFD });
	// TODO 46. command ???
	// TODO check numbers of instructions, (for example if 0xFD equals to DCL command, so make a test)

	sourcefile.open(filename.c_str(), ios::in);

	if (sourcefile.is_open()) {
		string line;

		while (getline(sourcefile, line)) {
			code.push_back(line);
		}

	} else {
		sourcefile.close();
		cout << "File " << filename << " wasn't open" << endl; // TODO after an implementing an exception, delete this cout
		throw "File was not opened"; // TODO throw exception file wasn't open
	}

}

Compiler::~Compiler() {
	sourcefile.close();
}

void Compiler::toCompile() {
	int address = 0; // Address of the current line (command)
	int lineNumber = 0;

	/*
	 * First passing
	 * Parsing and saving to tables
	 */

	for (string &line : code) {
		string currentLine = line;

		string label;
		string instruction;
		string operand;
		string operandLeft;
		string operandRight;

		lineNumber++;

		parseLine(line, label, instruction, operand, operandLeft, operandRight, lineNumber);

		saveToTables(currentLine, label, instruction, operandLeft, operandRight, lineNumber, address);

		address += getInstructionLength(instruction);

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

	if (outputfile.is_open()) {

        for (const Instruction& i : instructionTable) {
			if (i.code & 0xFF00) {
				outputfile << (char) ((i.code & 0xFF00) >> 8);
			}

			outputfile << (char) (i.code & 0xFF);

		}

		outputfile.close();
	} else {
		throw "File was not created";
	}

}// toCompile

vector<Error> Compiler::getErrors() const
{
    return errors;
}

vector<Instruction> Compiler::getInstructionTable() const
{
    return instructionTable;
}


