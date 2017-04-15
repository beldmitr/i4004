/*
 * SourceCode.h
 *
 *  Created on: 16. 8. 2016
 *  Author: user
 */

#ifndef COMPILER_H_
#define COMPILER_H_

//#include <QString>

#include <iostream>
#include <fstream>
#include <vector>
//#include <string>
#include <regex>
//#include <sstream>

//#include "error.h"
#include "Interfaces/icompiler.h"

#include "Compiler/operand.h"

#include "Compiler/commandset.h"


// TODO delete unused headers
class Compiler : public ICompiler {
private:
//    // Nested classes
//    class Constants {
//    public:
//        std::string label;
//        std::string constant;
//    };

//    class Labels {
//    public:
//        std::string label;
//        int address;
//    };

//    class Instruct
//    {
//    public:
//        std::string name;
//        std::string operandLeft;
//        std::string operandRight;
//        std::string line;
//        int lineNumber;
//        int code;

//        Instruct(std::string name, std::string operandLeft, std::string operandRight,
//                    std::string line, int lineNumber, int code);
//    };

//    // Variables
//    std::vector<Error> errors;

//	ifstream sourcefile;	// File where is saved a source code
//	ofstream outputfile;
//    std::string output="";

//    std::vector<std::string> code;	// Source code is here
//    std::vector<int> objectcode;

//    std::vector<Instruct> instructionTable;
//    std::vector<Constants> constantsTable;
//    std::vector<Labels> labelsTable;

//    // Methods



////    bool checkLabelExist(const std::string&);

////    std::string getConstByLabel(const std::string&);
////    int getAddressByLabel(const std::string&);

//    void saveToTables(const std::string&, const std::string&, const std::string&,
//                      const std::string&, const std::string&, const int&, const int&);
//    void parseLine(std::string&, std::string&, std::string&, std::string&,
//                   std::string&, std::string&, const int&);
//	void preprocessing();
//	void composing();

////    void checkNoOperands(const Instruct&);
////    void checkLeftOperandCondition(Instruct&);
////    void checkLeftOperandAddress(Instruct&);
////    void checkRightOperandAddress(Instruct&);
////    void checkRightOperandData(Instruct&);
////    void checkLeftOperandPair(const Instruct&);
////    void checkNoRightOperand(const Instruct&);
////    void checkLeftOperandRegister(const Instruct&);
////    void checkLeftOperandData(Instruct&);

//public:
//    explicit Compiler(const std::string& filename, const std::string& output);
//	virtual ~Compiler();

//    virtual void toCompile();
//    virtual vector<Error> getErrors() const;
//    virtual vector<unsigned int> getCompiledCode() const;
};

#endif /* COMPILER_H_ */
