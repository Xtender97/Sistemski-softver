#pragma once
#include <vector>
#include "TNSRow.h"

class TNS{

    vector<TNSRow*> tns;

    TNS();
    bool isEmtry();
    void calculate();
};