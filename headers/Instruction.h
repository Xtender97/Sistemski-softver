#pragma once
#include <iostream>
#include <unordered_map>
#include "Line.h"
#include "Operand.h"

using namespace std;

enum Type
{
    JUMP,
    DATA,
    NO_OPERAND
};

struct InstructionInfo
{
    int opCode;
    Type type;
    int numberOfOperands;
};

enum OperandSize
{
    BYTE,
    WORD,
    IMPLICIT
};
class Instruction : public Line
{
private:
    static unordered_map<string, InstructionInfo> InstructionMap;
    static unordered_map<string, int> RegisterMap;
   


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
};

Instruction *createInstruction(string instruction);
