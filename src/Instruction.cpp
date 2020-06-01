#include "../headers/Instruction.h"
#include <regex>
#include "../headers/regex.h"
#include "../headers/print.h"
#include "../headers/Assembler.h"

//MAP OF INSTRUCTIONS WITH MNEMONIC, OP CODE, TYPE OF INSTRUCTION AMD NUMBER OF OPERANDS

unordered_map<string, InstructionInfo> Instruction::InstructionMap = {
    {"halt", {0, NO_OPERAND, 0}},
    {"iret", {1, NO_OPERAND, 0}},
    {"ret", {2, NO_OPERAND, 0}},
    {"int", {3, JUMP, 1}},
    {"call", {4, JUMP, 1}},
    {"jmp", {5, JUMP, 1}},
    {"jeq", {6, JUMP, 1}},
    {"jne", {7, JUMP, 1}},
    {"jgt", {8, JUMP, 1}},
    {"push", {9, DATA, 1}},
    {"pop", {10, DATA, 1}},
    {"xchg", {11, DATA, 2}},
    {"mov", {12, DATA, 2}},
    {"add", {13, DATA, 2}},
    {"sub", {14, DATA, 2}},
    {"mul", {15, DATA, 2}},
    {"div", {16, DATA, 2}},
    {"cmp", {17, DATA, 2}},
    {"not", {18, DATA, 2}},
    {"and", {19, DATA, 2}},
    {"or", {20, DATA, 2}},
    {"xor", {21, DATA, 2}},
    {"test", {22, DATA, 2}},
    {"shl", {23, DATA, 2}},
    {"shr", {24, DATA, 2}}};

//CONSTRUCTOR

Instruction::Instruction(string mnemonic, string opOne, string opTwo, string label) : Line(!label.empty(), label, false, true)
{
    name = mnemonic;
    type = InstructionMap[mnemonic].type;
    opCode = InstructionMap[mnemonic].opCode;
    numberOfOperands = InstructionMap[mnemonic].numberOfOperands;
    sizeOfOperands = IMPLICIT;
    if (numberOfOperands >= 1)
    {
        operandOne = Operand(opOne, type);
    }

    if (numberOfOperands == 2)
    {
        operandTwo = Operand(opTwo, type);
    }

    if (numberOfOperands == 2 && operandTwo.adressing == IMMEDIATE)
    {
        throw "Destination argument can't be immediate!";
    }

    // if (numberOfOperands == 1 && name != "push" && operandOne.adressing == IMMEDIATE)
    // {
    //     throw "Destination argument can't be immediate! " + operandOne.stringOperand;
    // }
};

// SETS OPERAND SIZES BASED ON INSTRUCTIN MNEMONIC EXTENSION w or b

void Instruction::setOperandSizes(string size)
{
    if (!size.empty())
    {
        sizeOfOperands = size == "b" ? OperandSize::BYTE : OperandSize::WORD;
    }
    else
    {
        sizeOfOperands = IMPLICIT;
    }

    if (numberOfOperands >= 1)
    {
        cout << "SETS OPERAND 1 SIZE" << endl;
        operandOne.operandSize = sizeOfOperands;
    }
    if (numberOfOperands == 2)
    {
        cout << "SETS OPERAND 2 SIZE" << endl;

        operandTwo.operandSize = sizeOfOperands;
    }
}

//PRITNS INSTRUCTION INFORMATION

void Instruction::print()
{
    Line::print();
    cout << "Instruction: " << name << endl;
    cout << "Type: ";
    if (type == JUMP)
    {
        cout << "JUMP" << endl;
    }
    if (type == DATA)
    {
        cout << "DATA" << endl;
    }

    if (type == NO_OPERAND)
    {
        cout << "NO_OPERAND" << endl;
    }

    cout << "Op code: " << opCode << endl;
    if (sizeOfOperands != IMPLICIT)
    {
        cout << "Size of operands: " << ((sizeOfOperands == BYTE) ? "BYTE" : "WORD") << endl;
    }
    cout << "Number of operands: " << numberOfOperands << endl;
    if (numberOfOperands >= 1)
    {
        cout << "Operand one: " << endl;
        operandOne.print();
    }
    if (numberOfOperands == 2)
    {

        cout << "Operand two: " << endl;
        operandTwo.print();
    }

    cout << endl;
}

//CREATES NEW INSTRUCTION (CALLS CONSTRUCTOR AND SETS OPERAND SIZES)

Instruction *createInstruction(string line, string label)
{
    Instruction *instruction;
    regex regex_no_operand(no_operands_instruction);
    smatch match;
    if (regex_match(line, match, regex_no_operand))
    {
        instruction = new Instruction(match.str(1), "", "", label);
        instruction->print();
    }

    regex regex_single_operand_jump_instruction(single_operand_jump_instruction);
    if (regex_match(line, match, regex_single_operand_jump_instruction))
    {
        instruction = new Instruction(match.str(1), match.str(2), "", label);
        instruction->setOperandSizes("");
        instruction->print();
    }

    regex regex_single_operand_data_instruction(single_operand_data_instruction);
    if (regex_match(line, match, regex_single_operand_data_instruction))
    {

        instruction = new Instruction(match.str(1), match.str(3), "", label);
        instruction->setOperandSizes(match.str(2));
        instruction->print();
    }

    regex regex_double_operand_instruction(double_operand_instruction);
    //cout << double_operand_instruction << endl;

    if (regex_match(line, match, regex_double_operand_instruction))
    {
        instruction = new Instruction(match.str(1), match.str(3), match.str(9), label);
        instruction->setOperandSizes(match.str(2));
        instruction->print();
    }

    return instruction;
};

short int Instruction::size()
{
    short int size = 1;
    if (numberOfOperands == 0)
    {
        return size;
    }
    if (numberOfOperands >= 1)
    {
        size += operandOne.size();
    }
    if (numberOfOperands == 2)
    {
        size += operandTwo.size();
    }

    return size;
}

void Instruction::assamble()
{

    unsigned char InstrDescr = (unsigned char)opCode;
    InstrDescr = InstrDescr << 3;
    if (sizeOfOperands != BYTE)
    {
        InstrDescr |= 0x04;
    }
    else
    {
        InstrDescr &= 0xfb;
    }
    InstrDescr &= 0xfc;
    // cout << "after bit operations";
    // cout << hex << right << setfill('0') << setw(2) << (int)InstrDescr << " ";
    vector<unsigned char> op1;
    vector<unsigned char> op2;
    if (numberOfOperands == 1)
    {

        op1 = operandOne.operandValue(2, this); // because little endian
    }
    if (numberOfOperands == 2)
    {
        op1 = operandOne.operandValue(2, this);
        op2 = operandTwo.operandValue(op1.size()+1+1, this);
    }

    vector<unsigned char> instructionOpCode;
    instructionOpCode.push_back(InstrDescr);
    instructionOpCode.insert(instructionOpCode.end(), op1.begin(), op1.end());
    if (numberOfOperands == 2)
    {
        instructionOpCode.insert(instructionOpCode.end(), op2.begin(), op2.end());
    }

    int i = 0;
    int instructionSize = size();
    unsigned char bytes[instructionSize];
    for (auto elem : instructionOpCode)
    {
        bytes[i++] = elem;
    }
    Assembler::currentSection->addContent(bytes, instructionSize);
}