#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include "../headers/lexer.h"
#include "../headers/Assembler.h"
#include "../headers/SymbolTable.h"
#include "../headers/SectionDirective.h"
#include "../headers/Section.h"

using namespace std;

Section *Assembler::currentSection = nullptr;
short int Assembler::LC = 0;
bool Assembler::run = true;
TNS *Assembler::tns = new TNS();
ofstream Assembler::outputFile = ofstream();

Assembler::Assembler(string file_path, string output_file_path)
{
    line_number = 0;
    LC = 0;
    //currentSection = nullptr;
    file = ifstream(file_path);
    outputFile = ofstream(output_file_path);
    symbol_table = SymbolTable::getInstance();
    run = true;
};

void Assembler::assamble()
{
    bool status = true;
    string str_line;
    try
    {
        while (getline(file, str_line) && run)
        {
            line_number++;
            str_line = regex_replace(str_line, regex("^\\s+"), "");
            if (str_line == "")
            {
                continue;
            }

            Line *line = match_line(str_line);

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
                if (line->hasLabel)
                {
                    Symbol *tableSymbol = SymbolTable::getInstance()->getSymbol(line->label);
                    if (tableSymbol == nullptr)
                    {
                        Symbol *symbol = new Symbol(line->label, currentSection, true, LC, 'l');
                        symbol_table->addSymbol(symbol);
                    }
                    else
                    {
                        if (tableSymbol->isDefined)
                        {
                            throw "Multiple definition of symbol: " + tableSymbol->name;
                        }
                        else
                        {
                            tableSymbol->isDefined = true;
                            tableSymbol->section = currentSection;
                            tableSymbol->value = LC;
                        }
                    }
                }
                line->assamble();
                LC += line->size();
            }
        }

        tns->calculate();
        symbol_table->sort();
        symbol_table->printSortedTable();
        //symbol_table->print();
        //symbol_table->printAllSectionContents();
        symbol_table->backPatch();

        symbol_table->printToFile();
        symbol_table->printAllSectionContents();
        symbol_table->printToFileSectionsAndRelocations();

        


        cout << "Exited with status " << status << endl;
    }
    catch (const char *msg)
    {
        cerr << "Error at line " << line_number << ":" << endl;
        cerr << msg << endl;
    }
    catch (string error)
    {
        cerr << "Error at line " << line_number << ":" << endl;
        cerr << error << endl;
    }
}