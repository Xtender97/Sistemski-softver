#pragma once
#include <vector>
#include "TNSRow.h"

class TNS{
public:
    vector<TNSRow*> tns;

    TNS();
    void add(TNSRow* row);
    void remove(TNSRow* row);
    bool isEmpty();
    void calculate();
};