#pragma once
#include "Directive.h"

class SectionDirective : public Directive
{
public:
    string section_name;

    SectionDirective(string name, string section, string label);

    void print();

};