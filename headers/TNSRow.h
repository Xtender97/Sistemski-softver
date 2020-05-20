#pragma once
#include <string>
#include <vector>
#include "EquDirective.h"


class TNSRow{

    std::string symbol;
    vector<ExpressionElem> expresion;

    TNSRow(string symbol, ExpressionElem expression);

    int calculateExpression();

    bool canBeCalculated();
};