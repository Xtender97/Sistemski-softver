#include "../headers/Operand.h"
#include <regex>
#include "../headers/regex.h"

string Operand::addressingType[] = {
    "IMMEDIATE",
    "REGISTER_DIRECT",
    "REGISTER_INDIRECT",
    "REGISTER_INDIRECT_WITH_OFFSET",
    "MEMORY",
    "ERROR"};

string Operand::operandType[] = {
    "LITERAL",
    "SIMBOL",
    "REGISTER",
    "ERROR"};

string Operand::registerPartType[] =
    {
        "HIGH",
        "LOW",
        "WHOLE",
        "NOT_REGISTER",
        "ERROR"};

Operand::Operand()
{
    stringOperand = "no operand";
};

Operand::Operand(string operand)
{
    stringOperand = operand;
    OperandInfo info = selectAdressingAndType(operand);
    type = info.type;
    adressing = info.adressing;
    registerPart = info.part;
};

//EXTRACTS INFORMATION ABOUT OPERAND FROM STRING

OperandInfo Operand::selectAdressingAndType(string operand)
{
    regex regex_data_single_operand(data_single_operand);
    smatch match;
    OperandInfo info;

    //DATA SINGLE OPERANDS

    if (regex_match(operand, match, regex_data_single_operand))
    {
        return extractDataSingleOperand(operand);
    }

    // JUMP SINGLE OPERAND

    regex regex_jump_single_operand(jump_single_operand);
    if (regex_match(operand, match, regex_jump_single_operand))
    {
        return extractJumpSingleOperand(operand);
    }

    info = {TYPE_ERROR, ADDR_ERROR, REG_PART_ERROR};
    return info;
}

//PARSES DATA SINGLE OPERAND

OperandInfo Operand::extractDataSingleOperand(string operand)
{
    OperandInfo info;
    smatch match;
    //IMMEDIATE AND LITERAL

    regex immediate_literal("\\$" + literal);
    if (regex_match(operand, match, immediate_literal))
    {
        info = {LITERAL, IMMEDIATE, NOT_REGISTER};
        return info;
    }

    //IMMEDIATE AND SIMBOL

    regex immediate_simbol("\\$" + simbol);
    if (regex_match(operand, match, immediate_simbol))
    {
        info = {SIMBOL, IMMEDIATE, NOT_REGISTER};
        return info;
    }

    //ABSOLUTE AND LITERAL

    regex regex_absolute_literal(literal);
    if (regex_match(operand, match, regex_absolute_literal))
    {
        info = {LITERAL, MEMORY, NOT_REGISTER};
        return info;
    }

    //ABSOLUTE AND SIMBOL

    regex regex_absolute_simbol(simbol);
    if (regex_match(operand, match, regex_absolute_simbol))
    {
        info = {SIMBOL, MEMORY, NOT_REGISTER};
        return info;
    }

    //REGISTER DIRECT

    regex regex_register_direct("%r[0-7](l|h)?");
    if (regex_match(operand, match, regex_register_direct))
    {
        RegisterPart register_part = WHOLE;
        if (match.str(1) != "")
        {
            register_part = match.str(1) == "h" ? HIGH : LOW;
        }
        info = {REGISTER, REGISTER_DIRECT, register_part};
        return info;
    }

    //REGISTER INDIRECT

    regex regex_register_indirect("\\(%r[0-7]\\)");
    if (regex_match(operand, match, regex_register_indirect))
    {
        info = {REGISTER, REGISTER_INDIRECT, WHOLE};
        return info;
    }

    info = {TYPE_ERROR, ADDR_ERROR, REG_PART_ERROR};
    return info;
}

//PARSES JUMP SINGLE OPERAND

OperandInfo Operand::extractJumpSingleOperand(string operand)
{
    OperandInfo info;
    smatch match;

    //SIMBOL

    regex regex_simbol("(\\*)?" + simbol);
    if (regex_match(operand, match, regex_simbol))
    {

        //SIMBOL AND ABSOLUTE

        if (match.str(1) == "*")
        {
            info = {SIMBOL, MEMORY, NOT_REGISTER};
            return info;
        }

        //SIMBOL AND IMMEDIATE
        else
        {
            info = {SIMBOL, IMMEDIATE, NOT_REGISTER};
            return info;
        }
    }

    //LITERAL

    regex regex_literal("(\\*)?" + literal);
    if (regex_match(operand, match, regex_literal))
    {

        //LITERAL AND ABSOLUTE

        if (match.str(1) == "*")
        {
            info = {LITERAL, MEMORY, NOT_REGISTER};
            return info;
        }

        //LITERAL AND IMMEDIATE
        else
        {
            info = {LITERAL, IMMEDIATE, NOT_REGISTER};
            return info;
        }
    }

    //REGISTER DIRECT

    regex regex_register_direct("\\*%r[0-7]");
    if (regex_match(operand, match, regex_register_direct))
    {

        info = {REGISTER, REGISTER_DIRECT, WHOLE};
        return info;
    }

    //REGISTER INDIRECT

    regex regex_register_indirect("\\*\\(%r[0-7]\\)");
    if (regex_match(operand, match, regex_register_indirect))
    {
        info = {REGISTER, REGISTER_INDIRECT, WHOLE};
        return info;
    }

    info = {TYPE_ERROR, ADDR_ERROR, REG_PART_ERROR};
    return info;
}



void Operand::print()
{
    cout << "Operand type: " << operandType[type] << endl;
    cout << "Operand adressing: " << addressingType[adressing] << endl;
    if (registerPart != NOT_REGISTER)
    {
        cout << "Operand register part: " << registerPartType[registerPart] << endl;
    }
}
