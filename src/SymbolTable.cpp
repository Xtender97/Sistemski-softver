#include "../headers/SymbolTable.h"
#include "../headers/Symbol.h"
#include "../headers/Section.h"
#include <iostream>
#include "../headers/print.h"
#include <algorithm>

SymbolTable::SymbolTable()
{
    max_serial = 0;
    symbolTable[".und"] = new Section("und", true, 0, 'l', max_serial);
    max_serial++;
}

SymbolTable *SymbolTable::instance = 0;

SymbolTable *SymbolTable::getInstance()
{
    if (instance == 0)
    {
        instance = new SymbolTable();
    }
    return instance;
}

void SymbolTable::addSymbol(Symbol *symbol)
{
    // if(symbolExists(symbol->name)){
    //     throw "Multiple definition of symbol: " + symbol->name;
    // }
    symbol->setSerialNumber(max_serial++);
    symbolTable[symbol->name] = symbol;
}

bool SymbolTable::symbolExists(string symbol_name)
{
    if (symbolTable.find(symbol_name) == symbolTable.end())
    {
        return false;
    }
    else
    {
        return true;
    }
}

Symbol *SymbolTable::getSymbol(string symbol_name)
{
    if (symbolExists(symbol_name))
    {
        return symbolTable[symbol_name];
    }
    else
        return nullptr;
};

void SymbolTable::print()
{
    printElement("Name", 25);
    printElement("Section", 10);
    printElement("isDefined", 10);
    printElement("Value", 16);
    printElement("Scope", 10);
    printElement("SerialNumber", 20);
    printElement("ForwardList", 20);
    cout << endl;
    for (auto elem : symbolTable)
    {
        elem.second->print();
    }
    cout << endl;
}

void SymbolTable::printAllSectionContents()
{
    for (auto elem : symbolTable)
    {

        if (dynamic_cast<Section *>(elem.second))
        {
            if (elem.second->name != ".und")
            {
                ((Section *)elem.second)->content->print();
                cout << endl;
                ((Section *)elem.second)->relocationTable->print();

                cout << endl;
            }
        }
    }
};

void SymbolTable::backPatch()
{
    for (auto elem : symbolTable)
    {
        if (!elem.second->forwardList.empty())
        {
            if (!elem.second->isDefined && elem.second->section->name != ".und")
            {
                throw "Symbol " + elem.second->name + " wasn't defined!";
            }
            for (auto el : elem.second->forwardList)
            {
                ((Section *)el.section)->content->replace(el.offset, el.size, elem.second->value);
            }
        }
    }
};

bool sortFunction(Symbol *i, Symbol *j)
{
    return (i->serialNumber < j->serialNumber);
};

void SymbolTable::sort()
{

    for (auto elem : symbolTable)
    {

        if (dynamic_cast<Section *>(elem.second))
        {
            sortedMap.push_back(elem.second);
        }
    }
    std::sort(sortedMap.begin(), sortedMap.end(), sortFunction);

    for (int i = 0; i < sortedMap.size(); i++)
    {
        sortedMap[i]->serialNumber = i;
    };

    int numberOfSections = sortedMap.size();

    for (auto elem : symbolTable)
    {

        if (dynamic_cast<Section *>(elem.second) == nullptr)
        {
            sortedMap.push_back(elem.second);
        }
    }

    std::sort(sortedMap.begin() + numberOfSections, sortedMap.end(), sortFunction);

    for (int i = numberOfSections - 1; i < sortedMap.size(); i++)
    {
        sortedMap[i]->serialNumber = i;
    };
}

void SymbolTable::printSortedTable()
{

    printElement("Name", 25);
    printElement("Section", 10);
    printElement("isDefined", 10);
    printElement("Value", 16);
    printElement("Scope", 10);
    printElement("SerialNumber", 20);
    printElement("ForwardList", 20);
    cout << endl;
    for (auto elem : sortedMap)
    {
        elem->print();
    }
    cout << endl;
}

void SymbolTable::printToFile()
{
    printElementToFile("#Tabela simbola", 100);
    Assembler::outputFile << endl;
    printElementToFile("#Name", 25);
    printElementToFile("Section", 10);
    // printElementToFile("isDefined", 10);
    printElementToFile("Value/Size", 16);
    printElementToFile("Scope", 10);
    printElementToFile("SerialNumber", 20);
    // printElementToFile("ForwardList", 20);
    Assembler::outputFile << endl;
    for (auto elem : sortedMap)
    {
        elem->printToFile();
    }
    Assembler::outputFile << endl;
};

void SymbolTable::printToFileSectionsAndRelocations()
{

    for (auto elem : symbolTable)
    {

        if (dynamic_cast<Section *>(elem.second))
        {
            if (elem.second->name != ".und")
            {
                ((Section *)elem.second)->relocationTable->printToFile();

                Assembler::outputFile << endl;
            }
        }
    }

    for (auto elem : symbolTable)
    {

        if (dynamic_cast<Section *>(elem.second))
        {
            if (elem.second->name != ".und")
            {
                ((Section *)elem.second)->content->printToFile();
                Assembler::outputFile << endl;
            }
        }
    }
};
