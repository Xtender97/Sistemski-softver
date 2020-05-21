#pragma once

#include <string>
#include <vector>

using namespace std;

class SectionContent
{

public:
    string sectionName;
    vector <unsigned char> content;

    SectionContent(string name);

    void append(unsigned char * content, int size);

    void replace(int index, int size, unsigned char * content);

    void print();

};