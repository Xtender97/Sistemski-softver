#include "../headers/RelocationTable.h"
#include <iostream>

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
    cout<< "Relocation table for section: " + sectionName << endl;
    for (auto elem : table)
    {
        elem->print();
    };
    std::cout << endl;
}