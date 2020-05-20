#pragma once
#include <iostream>

using namespace std;

class Line
{
public:
    bool hasLabel;
    bool isDirective;
    bool isInstruction;
    string label;
    Line(bool hasLabel, string label, bool isDirective, bool isInstruction);
    virtual void print();
    virtual short int size();
};