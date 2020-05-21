#include "../headers/Symbol.h"
#include <iostream>
#include "../headers/print.h"

using namespace std;

Symbol::Symbol(string name, int section_serial, bool isDefinition, int val, char scope, int serialNumber)
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
}

Symbol::Symbol(string name, int section_serial, bool isDefinition, int val, char scope)
{
    this->name = name;
    section = section_serial;
    isDefined = isDefinition;
    if (isDefined)
    {
        value = val;
    }
    this->scope = scope;
}

void Symbol::addToForwardList(int offset)
{
    forwardList.push_back(offset);
}

void Symbol::print()
{

    printElement(name, 25);
    printElement(section, 10);
    printElement(isDefined, 10);
    printElement(value, 16);
    printElement(scope, 10);
    printElement(serialNumber, 20);

    //cout << "Symbol:" << name << " " << section << " " << isDefined << " " << value << " " << scope << " " << serialNumber << endl;

    if (!forwardList.empty())
    {
        for (auto elem : forwardList)
        {
            printElement(elem, 8);
            cout << " ";
        }
    }
    cout << endl;
}

void Symbol::setSerialNumber(int serial)
{
    serialNumber = serial;
};