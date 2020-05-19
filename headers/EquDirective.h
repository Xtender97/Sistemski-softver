#pragma once
#include "Directive.h"
#include <vector>
#include "Enums.h"

struct ExpressionElem
{
    Sign sign;
    ListType type;
    string value;
};

class EquDirective : public Directive
{
public:
    vector<ExpressionElem> expression_list;
    string simbol_name;
    EquDirective(string name, string equ_simbol, string expr, string label);
    void print();
};