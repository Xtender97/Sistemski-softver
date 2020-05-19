#pragma once
#include <string>
#include <vector>

using namespace std;

class Symbol{
public:

    string name;
    int section;
    bool isDefined;
    short int value;
    int serialNumber;
    char scope;
    vector<int> forwardList;

    Symbol(string n, int section_serail, bool definition, int val, char global_or_local);

    void backPatch();
};

