/*
 * SourceCode.h
 *
 *  Created on: 16. 8. 2016
 *  Author: user
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
#include "Interfaces/icompiler.h"

class Compiler : public ICompiler {
private:
    // Nested classes
    class Constants {
    public:
        std::string label;
        std::string constant;
    };

    class Labels {
    public:
        std::string label;
        int address;
    };

    class InstructionSet {
    public:
        std::string mnemonic;
        int code;	// TODO Maybe change to Byte or DByte
    };

    class Instruction
    {
    public:
        std::string name;
        std::string operandLeft;
        std::string operandRight;
        std::string line;
        int lineNumber;
        int code;

        Instruction(std::string name, std::string operandLeft, std::string operandRight,
                    std::string line, int lineNumber, int code);
    };

    // Variables

    std::vector<Error> errors;

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

    std::vector<InstructionSet> set;	// Instruction Set

	ifstream sourcefile;	// File where is saved a source code
	ofstream outputfile;
    std::string output="";

    std::vector<std::string> code;	// Source code is here
    std::vector<int> objectcode;

    std::vector<Instruction> instructionTable;
    std::vector<Constants> constantsTable;
    std::vector<Labels> labelsTable;

    // Methods

    std::string trimStrong(const std::string&); // Delete all whitespaces from string
    std::string trim(const std::string&);
    bool checkLabelExist(const std::string&);
	int getInstructionLength(const string&);
    std::string getConstByLabel(const std::string&);
    int getAddressByLabel(const std::string&);
    int getCodeByInstruction(const std::string&);

    bool isInstruction(const std::string&) const;

    void saveToTables(const std::string&, const std::string&, const std::string&,
                      const std::string&, const std::string&, const int&, const int&);
    void parseLine(std::string&, std::string&, std::string&, std::string&,
                   std::string&, std::string&, const int&);
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

    int register2int(const std::string&) const;
    int pair2int(const std::string&) const;
    int condition2int(const std::string&) const;
    int address2int(const std::string&) const;
    int bin2int(const std::string&) const; //TODO
    int hex2int(const std::string&) const; //TODO
    int dec2int(const std::string&) const;
    int to4bit(const int&) const; // FIXME what is const int& , maybe only int ??
    int to8bit(const int&) const; // FIXME what is const int& , maybe only int ??
	int to12bit(const int&) const;
	int to4bitStrong(const int&) const;
	int to8bitStrong(const int&) const;
	int to12bitStrong(const int&) const;


public:
    explicit Compiler(const std::string& filename, const std::string& output);
	virtual ~Compiler();

    virtual void toCompile();
    virtual vector<Error> getErrors() const;
    virtual vector<unsigned int> getCompiledCode() const;
};

#endif /* COMPILER_H_ */
