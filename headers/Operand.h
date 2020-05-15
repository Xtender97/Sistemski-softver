#pragma once
#include <iostream>
#include <unordered_map>
#include "Enums.h"

using namespace std;



struct OperandInfo
{
    OperandType type;
    AddressingType adressing;
    RegisterPart part;
    string reg;
    string simbol;
    string literal;
};

class Operand
{
private:
    static string addressingType[];
    static string operandType[];
    static string registerPartType[];

public:
    string stringOperand;
    OperandType type;
    AddressingType adressing;
    RegisterPart registerPart;

    string op_reg;
    string op_simbol;
    string op_literal;

    //dont use at the moment
    int RegOpCode;

    Operand();
    Operand(string operand, Type instruction_type);

    OperandInfo selectAdressingAndType(string operand, Type instruction_type);

    OperandInfo extractDataSingleOperand(string operand);
    OperandInfo extractJumpSingleOperand(string operand);
    OperandInfo extractJumpDoubleOperand(string operand);
    OperandInfo extractDataDoubleOperand(string operand);
    void print();
};
