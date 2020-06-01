#include "../headers/Operand.h"
#include <regex>
#include "../headers/regex.h"
#include "../headers/Assembler.h"
#include "../headers/Instruction.h"

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
    "LITERAL_REGISTER",
    "SIMBOL_REGISTER",
    "ERROR"};

string Operand::registerPartType[] =
    {
        "HIGH",
        "LOW",
        "WHOLE",
        "NOT_REGISTER",
        "ERROR"};

unordered_map<string, unsigned char> Operand::RegisterMap = {
    {"r0", 0x00},
    {"r1", 0x01},
    {"r2", 0x02},
    {"r3", 0x03},
    {"r4", 0x04},
    {"r5", 0x05},
    {"r6", 0x06},
    {"r7", 0x07},
    {"pc", 0x07},
    {"psw", 0x0f}};

unordered_map<AddressingType, unsigned char> Operand::AddressingMap{

    {IMMEDIATE, 0x00},
    {REGISTER_DIRECT, 0x01},
    {REGISTER_INDIRECT, 0x02},
    {REGISTER_INDIRECT_WITH_OFFSET, 0x03},
    {MEMORY, 0x04}

};

Operand::Operand()
{
    stringOperand = "no operand";
};

Operand::Operand(string operand, Type instruction_type)
{
    stringOperand = operand;
    OperandInfo info = selectAdressingAndType(operand, instruction_type);
    type = info.type;
    adressing = info.adressing;
    registerPart = info.part;
    op_reg = info.reg;
    op_simbol = info.simbol;
    op_literal = info.literal;
};

//EXTRACTS INFORMATION ABOUT OPERAND FROM STRING

OperandInfo Operand::selectAdressingAndType(string operand, Type instruction_type)
{
    regex regex_data_single_operand(data_single_operand);
    smatch match;
    OperandInfo info;

    //DATA SINGLE OPERANDS

    if (regex_match(operand, match, regex_data_single_operand) && instruction_type == DATA)
    {
        return extractDataSingleOperand(operand);
    }

    // JUMP SINGLE OPERAND

    regex regex_jump_single_operand(jump_single_operand);
    if (regex_match(operand, match, regex_jump_single_operand) && instruction_type == JUMP)
    {
        return extractJumpSingleOperand(operand);
    }

    //JUMP DOUBLE OPERAND

    regex regex_jump_double_operand(jump_double_operand);
    if (regex_match(operand, match, regex_jump_double_operand))
    {
        return extractJumpDoubleOperand(operand);
    }

    //DATA DOUBLE OPERAND

    regex regex_data_double_operand(data_double_operand);
    if (regex_match(operand, match, regex_data_double_operand))
    {
        return extractDataDoubleOperand(operand);
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

    regex immediate_literal("\\$(" + literal + ")");
    // cout << "Immediate literal regex: " << "\\$" + literal << endl;
    if (regex_match(operand, match, immediate_literal))
    {
        info = {LITERAL, IMMEDIATE, NOT_REGISTER, "none", "none", match.str(1)};
        return info;
    }

    //IMMEDIATE AND SIMBOL

    regex immediate_simbol("\\$(" + simbol + ")");
    if (regex_match(operand, match, immediate_simbol))
    {
        info = {SIMBOL, IMMEDIATE, NOT_REGISTER, "none", match.str(1), "none"};
        return info;
    }

    //ABSOLUTE AND LITERAL

    regex regex_absolute_literal(literal);
    if (regex_match(operand, match, regex_absolute_literal))
    {
        info = {LITERAL, MEMORY, NOT_REGISTER, "none", "none", match.str(0)};
        return info;
    }

    //ABSOLUTE AND SIMBOL

    regex regex_absolute_simbol(simbol);
    if (regex_match(operand, match, regex_absolute_simbol))
    {
        info = {SIMBOL, MEMORY, NOT_REGISTER, "none", match.str(0), "none"};
        return info;
    }

    //REGISTER DIRECT

    regex regex_register_direct("%(r[0-7])(l|h)?");
    if (regex_match(operand, match, regex_register_direct))
    {
        RegisterPart register_part = WHOLE;
        if (!match.str(2).empty())
        {
            register_part = match.str(2) == "h" ? HIGH : LOW;
        }
        info = {REGISTER, REGISTER_DIRECT, register_part, match.str(1), "none", "none"};
        return info;
    }

    //REGISTER INDIRECT

    regex regex_register_indirect("\\(%(r[0-7])\\)");
    if (regex_match(operand, match, regex_register_indirect))
    {
        info = {REGISTER, REGISTER_INDIRECT, WHOLE, match.str(1), "none", "none"};
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

    regex regex_simbol("(\\*)?(" + simbol + ")");
    if (regex_match(operand, match, regex_simbol))
    {

        //SIMBOL AND ABSOLUTE

        if (match.str(1).compare("*") == 0)
        {
            info = {SIMBOL, MEMORY, NOT_REGISTER, "none", match.str(2), "none"};
            return info;
        }

        //SIMBOL AND IMMEDIATE
        else
        {
            info = {SIMBOL, IMMEDIATE, NOT_REGISTER, "none", match.str(2), "none"};
            return info;
        }
    }

    //LITERAL

    regex regex_literal("(\\*)?(" + literal + ")");
    if (regex_match(operand, match, regex_literal))
    {

        //LITERAL AND ABSOLUTE

        if (match.str(1).compare("*") == 0)
        {
            info = {LITERAL, MEMORY, NOT_REGISTER, "none", "none", match.str(2)};
            return info;
        }

        //LITERAL AND IMMEDIATE
        else
        {
            info = {LITERAL, IMMEDIATE, NOT_REGISTER, "none", "none", match.str(2)};
            return info;
        }
    }

    //REGISTER DIRECT

    regex regex_register_direct("\\*%(r[0-7])");
    if (regex_match(operand, match, regex_register_direct))
    {

        info = {REGISTER, REGISTER_DIRECT, WHOLE, match.str(1), "none", "none"};
        return info;
    }

    //REGISTER INDIRECT

    regex regex_register_indirect("\\*\\(%(r[0-7])\\)");
    if (regex_match(operand, match, regex_register_indirect))
    {
        info = {REGISTER, REGISTER_INDIRECT, WHOLE, match.str(1), "none", "none"};
        return info;
    }

    info = {TYPE_ERROR, ADDR_ERROR, REG_PART_ERROR};
    return info;
}

OperandInfo Operand::extractJumpDoubleOperand(string operand)
{
    OperandInfo info;
    smatch match;

    // WITH SIMOBOL

    regex regex_simbol_register("\\*(" + simbol + ")\\(%(r[0-7]|pc)\\)"); // % moved in fornt of or
    if (regex_match(operand, match, regex_simbol_register))
    {
        info = {SIMBOL_REGISTER, REGISTER_INDIRECT_WITH_OFFSET, WHOLE, match.str(2), match.str(1), "none"};
        return info;
    }

    // WITH LITERAL

    regex regex_literal_register("\\*(" + literal + ")\\(%(r[0-6])\\)");
    if (regex_match(operand, match, regex_literal_register))
    {
        info = {LITERAL_REGISTER, REGISTER_INDIRECT_WITH_OFFSET, WHOLE, match.str(2), "none", match.str(1)};
        return info;
    }

    info = {TYPE_ERROR, ADDR_ERROR, REG_PART_ERROR};
    return info;
}

OperandInfo Operand::extractDataDoubleOperand(string operand)
{
    OperandInfo info;
    smatch match;

    //WITH SIMBOL

    regex regex_simbol_register("(" + simbol + ")\\(%(r[0-7]|pc)\\)"); // % moved in fornt of or
    if (regex_match(operand, match, regex_simbol_register))
    {
        info = {SIMBOL_REGISTER, REGISTER_INDIRECT_WITH_OFFSET, WHOLE, match.str(2), match.str(1), "none"};
        return info;
    }

    // WITH LITERAL

    regex regex_literal_register("(" + literal + ")\\(%(r[0-6])\\)");
    if (regex_match(operand, match, regex_literal_register))
    {
        info = {LITERAL_REGISTER, REGISTER_INDIRECT_WITH_OFFSET, WHOLE, match.str(2), "none", match.str(1)};
        return info;
    }

    info = {TYPE_ERROR, ADDR_ERROR, REG_PART_ERROR};
    return info;
}

void Operand::print()
{
    cout << "\tOperand type: " << operandType[type] << endl;
    cout << "\tOperand adressing: " << addressingType[adressing] << endl;
    if (registerPart != NOT_REGISTER)
    {
        cout << "\tOperand register part: " << registerPartType[registerPart] << endl;
    }

    cout << "\tRegister: " << op_reg << endl;
    cout << "\tSimbol: " << op_simbol << endl;
    cout << "\tLiteral: " << op_literal << endl;
}

short int Operand::size()
{

    if (adressing == REGISTER_DIRECT || adressing == REGISTER_INDIRECT)
    {
        return 1;
    }
    if (adressing == REGISTER_INDIRECT_WITH_OFFSET || adressing == MEMORY)
    {
        return 3;
    }

    if (adressing == IMMEDIATE && operandSize == IMPLICIT)
    {
        if (type == SIMBOL)
        { // simbol predstavlja adresu mora da bude 16bita
            return 3;
        }
        if (type == LITERAL)
        {
            if (stoi(op_literal) <= 255)
            { // literal staje u 1 bajt
                return 2;
            }
            else
            {
                return 3; // trebaju 2 bajta
            }
        }
    }
    if (adressing == IMMEDIATE && operandSize == BYTE)
    { //
        return 2;
    }
    if (adressing == IMMEDIATE && operandSize == WORD)
    {
        return 3;
    }

    cout << "ERROR" << endl;
    cout << operandSize << endl;
    return 0; // greska
};

vector<unsigned char> Operand::operandValue(int offsetFromBeginningOfInstruction, Instruction* instruction)
{
    vector<unsigned char> opCode;
    unsigned char OpDescr = 0x00;
    OpDescr |= (AddressingMap[adressing] << 5);
    if (adressing != IMMEDIATE && adressing != MEMORY)
    {
        OpDescr |= (RegisterMap[op_reg] << 1);
    }
    if (registerPart == HIGH)
    {
        OpDescr |= 0x01;
    }
    opCode.push_back(OpDescr);

    short int offset = Assembler::LC;
    offset += offsetFromBeginningOfInstruction;
    short int value = 0;
    Section *currentSection = Assembler::currentSection;
    int opSize = size() - 1; // size of operand minus descrpitor
    if (type == SIMBOL || type == SIMBOL_REGISTER)
    {
        Symbol *symbol = SymbolTable::getInstance()->getSymbol(op_simbol);
        if (symbol != nullptr) //exists in table
        {
            if (symbol->isDefined)
            { //defined symbol
                value = symbol->value;
            }
            else
            { //not defined symbol
                symbol->addToForwardList(offset, currentSection, opSize);
                value = 0;
            }
        }
        else //doesnt existi in table
        {
            symbol = new Symbol(op_simbol, currentSection, false, 0, 'l');
            SymbolTable::getInstance()->addSymbol(symbol);
            symbol->addToForwardList(offset, currentSection, opSize);

            value = 0;
        }

        RelocationRecord *relocation;
        RelocationType type = R_386_16;

        if (adressing == REGISTER_INDIRECT_WITH_OFFSET && (op_reg == "r7" || op_reg == "pc"))
        {
            type = R_386_PC16;
            if(offsetFromBeginningOfInstruction > 2){// drugi operand
                value -= 2;
            }
            else{//prvi operand
                value -= 2;
                if(instruction->numberOfOperands ==2){
                    value -= instruction->operandTwo.size();
                }
            }
        }

        if (symbol->scope == 'g')
        {
            relocation = new RelocationRecord(offset, type, symbol, false);
        }
        else
        { //global symbol, reference section
            relocation = new RelocationRecord(offset, type, symbol, true);
        }
        currentSection->addRelocation(relocation);
        //symbol->addToOffsetList(relocation);
    }
    if (type == LITERAL_REGISTER || type == LITERAL)
    {
        value = stoi(op_literal);
        // cout << "VREDNOST LITERALA JE ********************************" + value << endl;
    }

    for (int i = 0; i <= opSize - 1; i++)
    {
        opCode.push_back(value >> (i * 8));
        cout << "operand" << endl;
    }
    return opCode;
    //currentSection->addContent(bytes, size);
};