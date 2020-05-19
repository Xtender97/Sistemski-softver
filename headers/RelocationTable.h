#pragma once
#include "RelocationRecord.h"

class RelocationTable
{
public:
    string sectionName;
    vector<RelocationRecord> table;

    RelocationTable(string name);

    void print();

    void addRelocation();
};