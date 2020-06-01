#include "../headers/RelocationRecord.h"
#include "../headers/print.h"

vector<string> RelocationRecord::RelocationTypeMap = {
    "R_386_8",
    "R_386_16",
    "R_386_PC16"};

RelocationRecord::RelocationRecord(short int offset, RelocationType type, Symbol *symbol, bool local)
{

    this->offset = offset;
    this->type = type;
    this->symbol = symbol;
    this->local = local;
};

void RelocationRecord::print()
{
    printElement(offset, 16);
    printElement(RelocationTypeMap[type], 15);
    if (!local)
    {
        printElement(symbol->serialNumber, 15);
    }
    else
    {
        printElement(symbol->section->serialNumber, 15);
    }
    cout << endl;
};