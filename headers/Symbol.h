#pragma once
#include <string>
#include <vector>

using namespace std;

class Symbol
{
public:
    string name;
    int section;
    bool isDefined;
    short int value;
    int serialNumber;
    char scope;
    vector<int> forwardList;

    Symbol(string name, int section_serial, bool isDefinition, int val, char scope, int serialNumber);

    Symbol(string name, int section_serial, bool isDefinition, int val, char scope);
    
    void backPatch();

    void addToForwardList(int offset);

    void print();

    void virtual setSerialNumber(int serial);
};
