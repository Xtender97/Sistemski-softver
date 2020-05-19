#pragma once

#include <string>
#include <vector>

class SectionContent
{

public:
    string sectionName;
    vector <char> content;

    SectionContent(string name);

    void append();

    void replace(int index, int size);

    void print();

};