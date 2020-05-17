#include "../headers/regex.h"

std::string literal = "\\d+";

std::string simbol = "(?!r[0-9])[a-zA-z]\\w*";

// matches single data operands like
//  <literal>, $<literal>, %r<num>, (%r<num>), <simbol>, $<simbol>, %r<num>h|l

std::string data_single_operand = "(\\$?" + simbol + "|\\$?" + literal + "|%r[0-7](l|h)?|\\(%r[0-7]\\))";

//cout << "DATA SINGLE OPERAND REGEX: " << data_single_operand << endl;

// matches single jump operands
//  *<literal>,  <literal>, *%r<num>, *(%r<num>), *<simbol>, <simbol>

std::string jump_single_operand = "(\\*?" + simbol + "|\\*?" + literal + "|\\*%r[0-7]|\\*\\(%r[0-7]\\))";
//cout << "JUMP SINGLE OPERAND REGEX: " << jump_single_operand << endl;

// matches double data operands like
// <literal>(%r<num>), <simbol>(%pc/%r<num>)
std::string data_double_operand = "(" + simbol + "\\((%r[0-7]|%pc)\\))|(" + literal + "\\(%r[0-6]\\))";
//cout << "DATA DOUBLE OPERAND REGEX: " << data_double_operand << endl;

//matches double jump operands like
// *<literal>(%r<num>), *<simbol>(%pc/%r<num>)
std::string jump_double_operand = "(\\*" + simbol + "\\((%r[0-7]|%pc)\\))|(\\*" + literal + "\\(%r[0-6]\\))";

std::string no_operands_instruction = "(halt|iret|ret)\\s*";

std::string single_operand_jump_instruction = "(int|call|jmp|jeq|jne|jgt)\\s+(" + jump_single_operand + "|" + jump_double_operand + ")\\s*";

std::string single_operand_data_instruction = "(push|pop)(b|w)?\\s+(" + data_single_operand + "|" + data_double_operand + ")\\s*";

std::string double_operand_instruction = "(xchg|mov|add|sub|mul|div|cmp|not|and|or|xor|test|shl|shr)(b|w)?\\s+(" + data_single_operand + "|" + data_double_operand + "),\\s+(" + data_single_operand + "|" + data_double_operand + ")\\s*";

std::string simbol_list = "(" + simbol + "(,\\s*" + simbol + ")*)";

std::string mixed_list = "((" + simbol + "|" + literal + ")(,\\s*" + simbol + "|,\\s*" + literal + ")*)";

// .global <lista_simbola>,  .extern <lista_simbola>, .byte <lista_simbola/literala>, .word <lista_simbola/literala>
std::string list_directive = "(\\.(global|extern)\\s+" + simbol_list + "\\s*)|(\\.(byte|word)\\s+" + mixed_list + ")\\s*";
//cout << "LIST DIRECTIVE: " << list_directive << endl;

//.end
std::string end_directive = "\\.(end)\\s*";
//cout << "END DIRECTIVE: " << end_directive << endl;

// .skip <literal>
std::string skip_directive = "\\.(skip)\\s+" + literal + "\\s*";
//cout << "SKIP DIRECTIVE: " << skip_directive << endl;

std::string expression = "(" + simbol + "|" + literal + ")\\s*((\\+|-)\\s?(" + simbol + "|" + literal + ")\\s?)*";

// .equ <simbol>, <izraz>
std::string equ_directive = "\\.(equ)\\s+" + simbol + ",\\s*" + expression + "\\s*";
//cout << "EQU DIRECTIVE: " << equ_directive << endl;

// .section <ime_sekcije>:
std::string section_directive = "\\.(section)\\s+" + simbol + ":\\s*";
//cout << "SECTION DIRECTIVE: " << section_directive << endl;

// labela:
std::string lonely_label = simbol + ":\\s*";

std::string directive = "(" + section_directive + ")|(" + equ_directive + ")|(" + skip_directive + ")|(" + end_directive + ")|(" + list_directive + ")";
std::string instruction = "(" + no_operands_instruction + ")|(" + single_operand_jump_instruction + ")|(" + single_operand_data_instruction + ")|(" + double_operand_instruction + ")";
// cout << instruction << endl;

// labela : <directive>|<instruction>
std::string label_line = "(" + lonely_label + ")(" + directive + "|" + instruction + ")";