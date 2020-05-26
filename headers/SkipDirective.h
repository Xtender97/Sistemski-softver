#pragma once
#include "Directive.h"
#include "Assembler.h"

class SkipDirective : public Directive
{
public:
    short int numberOfBytes;

    SkipDirective(string name, int skipSize, string label);

    void print();

    short int size();

    void assamble();
};