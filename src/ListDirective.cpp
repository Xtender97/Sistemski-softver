#include "../headers/ListDirective.h"
#include <iostream>
#include "../headers/Directive.h"
#include "../headers/regex.h"
#include <regex>
#include "../headers/Enums.h"
#include "../headers/Assembler.h"
#include "../headers/Section.h"
#include "../headers/SymbolTable.h"

using namespace std;

ListDirective::ListDirective(string name, string list, string label) : Directive(name, label)
{

    regex regex_elem(simbol + "|" + literal);

    //cout << simbol + "|" + literal << endl;

    regex regex_simbol(simbol);
    regex regex_literal(literal);

    smatch match;

    while (regex_search(list, match, regex_elem))
    {
        string elem = match.str();
        // cout << match.str() << endl;
        // cout << "Elemnt:" << elem << endl;
        smatch match_inner;
        if (regex_match(elem, match_inner, regex_simbol))
        {
            //cout << "Simbol" << endl;
            Elem e = {SIMBOL_ELEM, elem};
            directive_list.push_back(e);
        }
        else
        {
            //cout << "Literal" << endl;

            Elem e = {LITERAL_ELEM, elem};
            directive_list.push_back(e);
        }

        list = match.suffix();
    };
}

void ListDirective::print()
{
    Directive::print();
    int i = 0;

    for (auto elem : directive_list)
    {
        i++;
        cout << "Element " << i << ". : " << elem.value << " of type " << (elem.type ? "SIMBOL" : "LITERAL") << endl;
    };

    cout << endl;
};

short int ListDirective::size()
{
    int multiplier = 0;
    if (type == WORD_DIRECTIVE)
    {
        multiplier = 2;
    };
    if (type == BYTE_DIRECTIVE)
    {
        multiplier = 1;
    };

    return directive_list.size() * multiplier;
}

void ListDirective::assamble()
{
    short int offset = Assembler::LC;
    Section *currentSection = Assembler::currentSection;
    if (type == WORD_DIRECTIVE || type == BYTE_DIRECTIVE)
    {
        int size = type == WORD_DIRECTIVE ? 2 : 1;
        for (auto elem : directive_list)
        {
            short int value = 0;
            if (elem.type == SIMBOL_ELEM)
            {
                Symbol *symbol = SymbolTable::getInstance()->getSymbol(elem.value);
                if (symbol != nullptr) //exists in table
                {
                    if (symbol->isDefined)
                    { //defined symbol
                        value = symbol->value;
                    }
                    else
                    { //not defined symbol

                        ///////////////////////////////////////////////
                        //   CREATE REALOCATION and set value to 0   //
                        ///////////////////////////////////////////////
                        value = 0;
                    }
                }
                else //doesnt existi in table
                {
                    ///////////////////////////////////////////////
                    //   CREATE REALOCATION and set value to 0   //
                    ///////////////////////////////////////////////
                    value = 0;
                }
            }
            else
            { //LITERAL
                value = stoi(elem.value);
                if (value > 255)
                {
                    throw "Operand of byte directive bigger then 255!";
                }
            }
            unsigned char bytes[size];
            for (int i = 0; i < size; i++)
                bytes[size - 1 - i] = (value >> (i * 8));

            currentSection->addContent(bytes, size);
            offset += size;
        }
    }

    if (type == GLOBAL)
    {
        if (currentSection != nullptr)
        {
            throw "Global directive cant be inside section!";
        }
        else
        {
            for (auto elem : directive_list)
            { // always symbol regex
                string symbol_name = elem.value;
                Symbol *symbol = new Symbol(symbol_name, nullptr, false, 0, 'g');
                SymbolTable::getInstance()->addSymbol(symbol);
            }
        }
    }
    if (type == EXTERN)
    {
        if (currentSection != nullptr)
        {
            throw "Extern directive cant be inside section!";
        }
        else
        {
            Section *undSection = (Section *)SymbolTable::getInstance()->getSymbol("und");
            for (auto elem : directive_list)
            { // always symbol regex
                string symbol_name = elem.value;
                Symbol *symbol = new Symbol(symbol_name, undSection, false, 0, 'g');
                SymbolTable::getInstance()->addSymbol(symbol);
            }
        }
    }
}