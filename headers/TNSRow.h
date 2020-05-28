#pragma once
#include <string>
#include <vector>
#include "EquDirective.h"


class TNSRow{
public:
    std::string symbol;
    vector<ExpressionElem> expression;

    TNSRow(string symbol, vector<ExpressionElem> expression);

    int calculateExpression();

    bool canBeCalculated();
};