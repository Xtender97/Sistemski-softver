#include "../headers/RelocationTable.h"
#include <iostream>
#include "../headers/Assembler.h"
#include "../headers/print.h"

RelocationTable::RelocationTable(string name)
{
    sectionName = name;
};

void RelocationTable::addRelocation(RelocationRecord *relocation)
{
    table.push_back(relocation);
}

void RelocationTable::print()
{
    cout << "Relocation table for section: " + sectionName << endl;
    for (auto elem : table)
    {
        if (elem->symbol->section) // znaci da je kontsantan simbol i ne treba ispisivati relokaciju
        {
            elem->print();
        }
    };
    std::cout << endl;
}

void RelocationTable::printToFile()
{
    Assembler::outputFile << "#.ret." + sectionName << endl;
    printElementToFile("#offset", 16);
    printElementToFile("tip", 15);
    printElementToFile("Serial number", 15);
    Assembler::outputFile << endl;
    for (auto elem : table)
    {
        if (elem->symbol->section) // znaci da nije kontsantan simbol i treba ispisivati relokaciju inace je ne ispisivati
        {
            elem->printToFile();
        }
    };
    Assembler::outputFile << endl;
}