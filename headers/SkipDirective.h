#pragma once
#include "Directive.h"

class SkipDirective : public Directive
{
public:
    int numberOfBytes;

    SkipDirective(string name, int skipSize, string label);

    void print();
};