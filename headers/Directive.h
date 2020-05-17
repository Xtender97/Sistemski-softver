#pragma once
#include "Enums.h"
#include "Line.h"
#include <unordered_map>

class Directive : public Line {
private:
    static unordered_map<string,DirectiveType> DirectiveTypesMap;

public:
    DirectiveType type;
    string directive_name;
    Directive(string name, string label);
    void print();
};