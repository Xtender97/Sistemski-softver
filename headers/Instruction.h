#pragma once
#include <iostream>
#include <unordered_map>
#include "Line.h"
#include "Operand.h"
#include "Enums.h"

using namespace std;




class Instruction : public Line
{
private:
    static unordered_map<string, InstructionInfo> InstructionMap;
   


public:
    string name;
    int opCode;
    Type type;

    int numberOfOperands;
    OperandSize sizeOfOperands;

    Operand operandOne;
    Operand operandTwo;

    Instruction(string mnemonic, string opOne, string opTwo, string label);

    void setOperandSizes(string size);

    void print();

    short int size();

    void assamble();
};

Instruction *createInstruction(string instruction, string label);
