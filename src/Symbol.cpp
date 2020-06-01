#include "../headers/Symbol.h"
#include <iostream>
#include "../headers/print.h"
#include "../headers/RelocationRecord.h"

using namespace std;

Symbol::Symbol(string name, Symbol *section_serial, bool isDefinition, int val, char scope, int serialNumber)
{
    this->name = name;
    section = section_serial;
    isDefined = isDefinition;
    if (isDefined)
    {
        value = val;
    }
    this->scope = scope;
    this->serialNumber = serialNumber;
    equDefined = false;
    relocationType = nullptr;

}

Symbol::Symbol(string name, Symbol *section_serial, bool isDefinition, int val, char scope)
{
    this->name = name;
    section = section_serial;
    isDefined = isDefinition;
    if (isDefined)
    {
        value = val;
    }
    this->scope = scope;
    equDefined = false;
    relocationType = nullptr;
}

void Symbol::addToForwardList(int offset, Symbol *section, int nmbOfBytes)
{
    forwardListElem elem = {offset, nmbOfBytes, section};
    forwardList.push_back(elem);
}

void Symbol::addToOffsetList(RelocationRecord *record)
{
    allOffsets.push_back(record);
};

void Symbol::print()
{

    printElement(name, 25);
    if (section)
    {
        printElement(section->serialNumber, 10);
    }
    else
    {
        printElement("nullptr", 10);
    }

    printElement(isDefined, 10);
    if (isDefined)
    {
        printElement(value, 16);
    }
    else
    {
        printElement(-1, 16);
    }
    printElement(scope, 10);
    printElement(serialNumber, 20);

    //cout << "Symbol:" << name << " " << section << " " << isDefined << " " << value << " " << scope << " " << serialNumber << endl;

    if (!forwardList.empty())
    {
        for (auto elem : forwardList)
        {
            printElement(elem.offset, 8);
            cout << " ";
        }
    }

    cout << " | ";

    if (!allOffsets.empty())
    {
        for (auto elem : allOffsets)
        {
            printElement(elem->offset, 8);
            cout << " ";
        }
    }
    cout << endl;
}

void Symbol::setSerialNumber(int serial)
{
    serialNumber = serial;
};

void Symbol::setEquDefined(){
    equDefined = true;
};

void Symbol::setRelocationType(RelocationRecord* record){
    relocationType = record;
};
