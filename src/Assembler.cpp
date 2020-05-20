#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include "../headers/lexer.h"
#include "../headers/Assembler.h"
#include "../headers/SymbolTable.h"

using namespace std;

Assembler::Assembler(string file_path)
{
    line_number = 0;
    LC = 0;
    currentSection = nullptr;
    file = ifstream(file_path);
    symbol_table = SymbolTable::getInstance();
    tns = nullptr;
};

void Assembler::assamble()
{
    bool status = true;
    string str_line;
    while (getline(file, str_line))
    {
        line_number++;
        str_line = regex_replace(str_line, regex("^\\s+"), "");
        if (str_line == "")
        {
            continue;
        }

        Line * line =match_line(str_line);

        if (line == nullptr)
        {
            status = false;
            cout << "Error at line: " << line_number << endl;
            cout << str_line << endl
                 << endl;
            break;
        }
        else
        {
            if(line->hasLabel){
                Symbol* symbol = new Symbol(line->label, /*currentSection->serialNumber*/ 0, true, LC, 'l');
                symbol_table->addSymbol(symbol);
            }

            

            LC += line->size();
        }
    }

    symbol_table->print();

    cout << "Exited with status " << status << endl;
}