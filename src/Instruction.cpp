#include "../headers/Instruction.h"
#include <regex>
#include "../headers/regex.h"

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
    {"pop", {10, DATA, 1}}

};
unordered_map<string, int> Instruction::RegisterMap = {
    {"r0", 0x0},
    {"r1", 0x1},
    {"r2", 0x2},
    {"r3", 0x3},
    {"r4", 0x4},
    {"r5", 0x5},
    {"r6", 0x6},
    {"r7", 0x7},
    {"pc", 0x7},
    {"psw", 0xf}};

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
        operandOne = Operand(opOne);
    }

    if (numberOfOperands == 2)
    {
        operandTwo = Operand(opTwo);
    }
};

// SETS OPERAND SIZES BASED ON INSTRUCTIN MNEMONIC EXTENSION w or b

void Instruction::setOperandSizes(string size)
{
    if (!size.empty())
    {
        sizeOfOperands = size == "b" ? BYTE : WORD;
    }
}

//PRITNS INSTRUCTION INFORMATION

void Instruction::print()
{
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

Instruction *createInstruction(string line)
{
    Instruction *instruction;
    regex regex_no_operand(no_operands_instruction);
    smatch match;
    if (regex_match(line, match, regex_no_operand))
    {
        instruction = new Instruction(match.str(1), "", "", "");
        instruction->print();
    }

    regex regex_single_operand_jump_instruction(single_operand_jump_instruction);
    if (regex_match(line, match, regex_single_operand_jump_instruction))
    {
        instruction = new Instruction(match.str(1), match.str(2), "", "");
        instruction->print();
    }

    regex regex_single_operand_data_instruction(single_operand_data_instruction);
    if (regex_match(line, match, regex_single_operand_data_instruction))
    {

        instruction = new Instruction(match.str(1), match.str(3), "", "");
        instruction->setOperandSizes(match.str(2));
        instruction->print();
    }

    return instruction;
};