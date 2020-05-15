#pragma once
#include <string>

extern std::string literal;

extern std::string simbol;

// matches single data operands like
//  <literal>, $<literal>, %r<num>, (%r<num>), <simbol>, $<simbol>, %r<num>h|l

extern std::string data_single_operand;

//cout << "DATA SINGLE OPERAND REGEX: " << data_single_operand << endl;

// matches single jump operands
//  *<literal>,  <literal>, *%r<num>, *(%r<num>), *<simbol>, <simbol>

extern std::string jump_single_operand;
//cout << "JUMP SINGLE OPERAND REGEX: " << jump_single_operand << endl;

// matches double data operands like
// <literal>(%r<num>), <simbol>(%pc/%r<num>)
extern std::string data_double_operand;
//cout << "DATA DOUBLE OPERAND REGEX: " << data_double_operand << endl;

//matches double jump operands like
// *<literal>(%r<num>), *<simbol>(%pc/%r<num>)
extern std::string jump_double_operand;

extern std::string no_operands_instruction;

extern std::string single_operand_jump_instruction;

extern std::string single_operand_data_instruction;

extern std::string double_operand_instruction;

extern std::string simbol_list;

extern std::string mixed_list;

// .global <lista_simbola>,  .extern <lista_simbola>, .byte <lista_simbola/literala>, .word <lista_simbola/literala>
extern std::string list_directive;
//cout << "LIST DIRECTIVE: " << list_directive << endl;

//.end
extern std::string end_directive;
//cout << "END DIRECTIVE: " << end_directive << endl;

// .skip <literal>
extern std::string skip_directive;
//cout << "SKIP DIRECTIVE: " << skip_directive << endl;

extern std::string expression;

// .equ <simbol>, <izraz>
extern std::string equ_directive;
//cout << "EQU DIRECTIVE: " << equ_directive << endl;

// .section <ime_sekcije>:
extern std::string section_directive;
//cout << "SECTION DIRECTIVE: " << section_directive << endl;

// labela:
extern std::string lonely_label;

extern std::string directive;
extern std::string instruction;
// cout << instruction << endl;

// labela : <directive>|<instruction>
extern std::string label_line;