#pragma once

#include <string>
#include <fstream>

#include "Section.h"
#include "SymbolTable.h"
#include "TNS.h"


using namespace std;

class Assembler
{
public:
    int line_number;
    static short int LC;
    static bool run;
    ifstream file;
    static ofstream outputFile;
    SymbolTable* symbol_table;
    static TNS* tns;


    static Section *currentSection;

    Assembler(string file_path, string output_file_path);

    void assamble();

    void printAll();
};