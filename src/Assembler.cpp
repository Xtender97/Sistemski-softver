#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include "../headers/lexer.h"
#include "../headers/Assembler.h"

using namespace std;

Assembler::Assembler(string file_path)
{
    line_number = 0;
    LC = 0;
    currentSection = nullptr;
    file = ifstream(file_path);
    // symbol_table = new SymbolTable();
    tns = nullptr;
};

void Assembler::assamble()
{
    bool status = true;
    string line;
    while (getline(file, line))
    {
        line_number++;
        line = regex_replace(line, regex("^\\s+"), "");
        if (line == "")
            continue;
        if (!match_line(line))
        {
            status = false;
            cout << "Error at line: " << line_number << endl;
            cout << line << endl
                 << endl;
            break;
        }
    }

    cout << "Exited with status " << status << endl;

}