#include "../headers/lexer.h"

string match_line(string line)
{

    string literal = "\\d+";

    string simbol = "[a-zA-z]\\w*";

    // matches single data operands like
    //  <literal>, $<literal>, %r<num>, (%r<num>), <simbol>, $<simbol>

    string data_single_operand = "(\\$?" + simbol + "|\\$?" + literal + "|%r[0-7]|\\(%r[0-7]\\))";

    //cout << "DATA SINGLE OPERAND REGEX: " << data_single_operand << endl;

    // matches single jump operands
    //  *<literal>,  <literal>, *%r<num>, *(%r<num>), *<simbol>, <simbol>

    string jump_single_operand = "(\\*?" + simbol + "|\\*?" + literal + "|\\*%r[0-7]|\\*\\(%r[0-7]\\))";
    //cout << "JUMP SINGLE OPERAND REGEX: " << jump_single_operand << endl;

    // matches double data operands like
    // <literal>(%r<num>), <simbol>(%pc/%r<num>)
    string data_double_operand = "(" + simbol + "\\((%r[0-7]|%pc)\\))|(" + literal + "\\(%r[0-6]\\))";
    //cout << "DATA DOUBLE OPERAND REGEX: " << data_double_operand << endl;

    //matches double jump operands like
    // *<literal>(%r<num>), *<simbol>(%pc/%r<num>)
    string jump_double_operand = "(\\*" + simbol + "\\((%r[0-7]|%pc)\\))|(\\*" + literal + "\\(%r[0-6]\\))";

    string no_operands_instruction = "(halt|iret|ret)\\s*";

    string single_operand_jump_instruction = "(int|call|jmp|jeq|jne|jgt)\\s+(" + jump_single_operand + "|" + jump_double_operand + ")\\s*";

    string single_operand_data_instruction = "(push|pop)\\s+(" + data_single_operand + "|" + data_double_operand + ")\\s*";

    string double_operand_instruction = "(xchg|mov|add|sub|mul|div|cmp|not|and|or|xor|test|shl|shr)\\s+(" + data_single_operand + "|" + data_double_operand + "),\\s+(" + data_single_operand + "|" + data_double_operand + ")\\s*";

    string simbol_list = "(" + simbol + "(,\\s*" + simbol + ")*)";

    string mixed_list = "((" + simbol + "|" + literal + ")(,\\s*" + simbol + "|,\\s*" + literal + ")*)";

    // .global <lista_simbola>,  .extern <lista_simbola>, .byte <lista_simbola/literala>, .word <lista_simbola/literala>
    string list_directive = "(\\.(global|extern)\\s+" + simbol_list + "\\s*)|(\\.(byte|word)\\s+" + mixed_list + ")\\s*";
    cout << "LIST DIRECTIVE: " << list_directive << endl;

    //.end
    string end_directive = "\\.end\\s*";
    cout << "END DIRECTIVE: " << end_directive << endl;

    // .skip <literal>
    string skip_directive = "\\.skip\\s+" + literal + "\\s*";
    cout << "SKIP DIRECTIVE: " << skip_directive << endl;

    string expression = "(" + simbol + "|" + literal + ")\\s*((\\+|-)\\s?(" + simbol + "|" + literal + ")\\s?)*";

    // .equ <simbol>, <izraz>
    string equ_directive = "\\.equ\\s+" + simbol + ",\\s*" + expression + "\\s*";
    cout << "EQU DIRECTIVE: " << equ_directive << endl;

    // .section <ime_sekcije>:
    string section_directive = "\\.section\\s+" + simbol + ":\\s*";
    cout << "SECTION DIRECTIVE: " << section_directive << endl;

    // labela:
    string lonely_label = simbol + ":\\s*";

    string directive = "(" + section_directive + ")|(" + equ_directive + ")|(" + skip_directive + ")|(" + end_directive + ")|(" + list_directive + ")";
    string instruction = "(" + no_operands_instruction + ")|(" + single_operand_jump_instruction + ")|(" + single_operand_data_instruction + ")|(" + double_operand_instruction + ")";

    // labela : <directive>|<instruction>
    string label_line = "(" + lonely_label + ")(" + directive + "|" + instruction + ")";

    regex reg(double_operand_instruction);

    smatch match;
    if (regex_match(line, match, reg))
    {
        cout << "For line: " << line << endl;
        cout << "First capture group: " << match.str(1) << endl;
        cout << "Second capture group: " << match.str(2) << endl;
        cout << "Third capture group: " << match.str(3) << endl;
        cout << "Fourth capture group: " << match.str(4) << endl;
        cout << "Fifth capture group: " << match.str(5) << endl;
        cout << "Sixth capture group: " << match.str(6) << endl
             << endl;
    }
    else
    {
        cout << "For line: " << line << endl;

        cout << "No match" << endl
             << endl;
    }

    return "A";
}