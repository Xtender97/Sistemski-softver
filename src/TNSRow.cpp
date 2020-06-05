#include "../headers/TNSRow.h"
#include "../headers/SymbolTable.h"
#include <unordered_map>
#include "../headers/Section.h"

TNSRow::TNSRow(string symbol, vector<ExpressionElem> expression)
{
    this->symbol = symbol;
    this->expression = expression;
}

int TNSRow::calculateExpression()
{
    int value = 0;
    for (auto elem : expression)
    {
        if (elem.type == LITERAL_ELEM)
        {
            if (elem.sign == MINUS)
            {
                value -= stoi(elem.value);
            }
            else
            {
                value += stoi(elem.value);
            }
        }
        else
        {
            if (elem.sign == MINUS)
            {
                value -= SymbolTable::getInstance()->getSymbol(elem.value)->value;
            }
            else
            {
                value += SymbolTable::getInstance()->getSymbol(elem.value)->value;
            }
        }
    }

    return value;
};

bool TNSRow::canBeCalculated()
{
    for (auto elem : expression)
    {
        if (elem.type == SIMBOL_ELEM)
        {
            Symbol *symbol = SymbolTable::getInstance()->getSymbol(elem.value);
            if (symbol != nullptr)
            {
                if (symbol->isDefined)
                {
                    //do nothing
                }
                else
                {
                    if (symbol->scope == 'g' && symbol->section->name == ".und")
                    { // ako je extern simbol
                    }
                    else
                    {
                        return false;
                    }
                }
            }
            else
            {
                return false;
            }
        }
    }
    return true;
};

Section *TNSRow::findRelocationType()
{

    unordered_map<Section *, int> classificationTable;
    for (auto elem : expression)
    {
        if (elem.type == SIMBOL_ELEM)
        {
            Section *sectionOfSymbol = (Section *)SymbolTable::getInstance()->getSymbol(elem.value)->section;

            if (classificationTable.find(sectionOfSymbol) == classificationTable.end())
            { // nova sekcija
                if (elem.sign == PLUS || sectionOfSymbol->name == ".und")
                {
                    classificationTable[sectionOfSymbol] = 1;
                }
                else
                {

                    classificationTable[sectionOfSymbol] = -1;
                }
            }
            else
            {

                if (elem.sign == PLUS || sectionOfSymbol->name == ".und")
                {
                    classificationTable[sectionOfSymbol]++;
                }
                else
                {
                    classificationTable[sectionOfSymbol]--;
                }
            }
        }
    }

    Section *relocationSection = nullptr;

    for (auto elem : classificationTable)
    {
        if (elem.second > 1 || elem.second < 0)
        {
            throw "Invalid definition in equ directive! Classification for section: " + elem.first->name;
        }

        if (relocationSection != nullptr && elem.second == 1)
        {
            throw "Invalid definition in equ directive! Relocatable for multiple sections!";
        }

        if (relocationSection == nullptr && elem.second == 1)
        {
            relocationSection = elem.first;
        }
    }

    return relocationSection;
};
