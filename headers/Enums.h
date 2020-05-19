#pragma once

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
    LITERAL_REGISTER,
    SIMBOL_REGISTER,
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

enum DirectiveType
{
    END,
    SKIP,
    GLOBAL,
    EXTERN,
    SECTION,
    BYTE_DIRECTIVE,
    WORD_DIRECTIVE,
    EQU
};

// TYPE OF ELEMNTS OF LISTS IN DIRECTIVES

enum ListType
{
    LITERAL_ELEM,
    SIMBOL_ELEM
};

enum Sign
{
    PLUS,
    MINUS
};

enum RelocationType{
    R_386_32,
    R_386_PC32
};