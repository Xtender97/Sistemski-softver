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
    int LC;
    ifstream file;
    SymbolTable* symbol_table;
    TNS* tns;


    Section *currentSection;

    Assembler(string file_path);

    void assamble();

    void printAll();
};