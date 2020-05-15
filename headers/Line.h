#pragma once
#include <iostream>

using namespace std;

class Line
{
public:
    bool m_hasLabel;
    bool m_isDirective;
    bool m_isInstruction;
    string m_label;
    Line(bool hasLabel, string label, bool isDirective, bool isInstruction);
};