/*
 * SourceCode.h
 *
 *  Created on: 16. 8. 2016
 *      Author: user
 */

#ifndef COMPILER_H_
#define COMPILER_H_

#include <QString>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <sstream>

#include "error.h"
#include "instruction.h"

using namespace std;

struct constants {
	string label;
	string constant;
};

struct labels {
	string label;
	int address;
};

struct instruction_set {
	string mnemonic;
	int code;	// TODO Maybe change to Byte or DByte
};

class Compiler {
private:
    vector<Error> errors;

	// Templates
	regex rLabel;
	regex rInstruction;
	regex rOperand;
	regex rComment;

	/*
	 *  rOpExpr not exact, always should be controlled on other regex.
	 *  If it is not a pair, register, label and so on, only in this case we may say, that it is a mathematical expression.
	 *  In other case we says, that it is not an expression
	 *  For example:
	 *  If rOpExpr equals true and other regex are false, we say that it is an expression.
	 *  If rOpExpr equals true and for example rOpPair is true, then rOpPair has greater priority and we say that it is a pair.
	 */
	regex rOpExpr;
	regex rOpPair;
	regex rOpRegister;
	regex rOpHex;
	regex rOpBin;
	regex rOpDec;
	regex rOpLabel;

	vector<instruction_set> set;	// Instruction Set

	ifstream sourcefile;	// File where is saved a source code
	ofstream outputfile;
	string output="";

	vector<string> code;	// Source code is here
	vector<int> objectcode;

    vector<Instruction> instructionTable;
	vector<constants> constantsTable;
	vector<labels> labelsTable;

	string trimStrong(const string&); // Delete all whitespaces from string
	string trim(const string&);
	bool checkLabelExist(const string&);
	int getInstructionLength(const string&);
    string getConstByLabel(const string&);
	int getAddressByLabel(const string&);
	int getCodeByInstruction(const string&);

	bool isInstruction(const string&) const;

	void saveToTables(const string&, const string&, const string&, const string&, const string&, const int&, const int&);
	void parseLine(string&, string&, string&, string&, string&, string&, const int&);
	void preprocessing();
	void composing();

    void checkNoOperands(const Instruction&);
    void checkLeftOperandCondition(Instruction&);
    void checkLeftOperandAddress(Instruction&);
    void checkRightOperandAddress(Instruction&);
    void checkRightOperandData(Instruction&);
    void checkLeftOperandPair(const Instruction&);
    void checkNoRightOperand(const Instruction&);
    void checkLeftOperandRegister(const Instruction&);
    void checkLeftOperandData(Instruction&);

	int register2int(const string&) const;
	int pair2int(const string&) const;
	int condition2int(const string&) const;
	int address2int(const string&) const;
	int bin2int(const string&) const; //TODO
	int hex2int(const string&) const; //TODO
	int dec2int(const string&) const;
	int to4bit(const int&) const;
	int to8bit(const int&) const;
	int to12bit(const int&) const;
	int to4bitStrong(const int&) const;
	int to8bitStrong(const int&) const;
	int to12bitStrong(const int&) const;


public:
    explicit Compiler(const string& filename, const string& output);
	virtual ~Compiler();

	void toCompile();
    vector<Error> getErrors() const;
    vector<Instruction> getInstructionTable() const;
};

#endif /* COMPILER_H_ */
