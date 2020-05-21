#include "../headers/RelocationRecord.h"
#include "../headers/print.h"

vector<string> RelocationRecord::RelocationTypeMap = {
    "R_386_32",
    "R_386_PC32"};

RelocationRecord::RelocationRecord(short int offset, RelocationType type, Symbol *symbol)
{

    this->offset = offset;
    this->type = type;
    this->symbol = symbol;
};

void RelocationRecord::print()
{
    printElement(offset, 16);
    printElement(RelocationTypeMap[type], 15);
    printElement(symbol->serialNumber, 15);
    cout << endl;
};