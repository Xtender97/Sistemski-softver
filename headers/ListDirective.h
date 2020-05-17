#pragma once
#include "Enums.h"
#include "Directive.h"
#include <vector>
struct Elem
{
    ListType type;
    string value;
};

class ListDirective : public Directive
{
public:
    vector<Elem> directive_list;
    ListDirective(string name, string list, string label);
    void print();
};