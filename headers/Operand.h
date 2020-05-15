#pragma once
#include <iostream>
#include <unordered_map>

using namespace std;

enum AddressingType
{
    IMMEDIATE,
    REGISTER_DIRECT,
    REGISTER_INDIRECT,
    REGISTER_INDIRECT_WITH_OFFSET,
    MEMORY,
    ADDR_ERROR
};
enum OperandType
{
    LITERAL,
    SIMBOL,
    REGISTER,
    TYPE_ERROR
};

enum RegisterPart
{
    HIGH,
    LOW,
    WHOLE,
    NOT_REGISTER,
    REG_PART_ERROR
};

struct OperandInfo
{
    OperandType type;
    AddressingType adressing;
    RegisterPart part;
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

    //dont use at the moment
    int RegOpCode;

    Operand();
    Operand(string operand);


    OperandInfo selectAdressingAndType(string operand);
    OperandInfo extractDataSingleOperand(string operand);
    OperandInfo extractJumpSingleOperand(string operand);
    void print();
};
