#include "../headers/SymbolTable.h"
#include "../headers/Symbol.h"
#include "../headers/Section.h"
#include <iostream>
#include "../headers/print.h"

SymbolTable::SymbolTable()
{
    max_serial = 0;
    symbolTable["und"] = new Section("und", 0, true, 0, 'l', max_serial);
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

void SymbolTable::printAllSectionContents(){
    for (auto elem : symbolTable)
    {
        if(elem.second->serialNumber == elem.second->section){
           ((Section*)elem.second)->content->print();
        }
    }
};
