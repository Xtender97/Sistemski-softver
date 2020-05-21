#include "../headers/SectionContent.h"
#include <string>
#include <iomanip>
#include <iostream>

SectionContent::SectionContent(string name)
{
    sectionName = name;
};

void SectionContent::append(unsigned char *content, int size)
{
    for (int i = size - 1; i >= 0; i--)
    {
        this->content.push_back(content[i]);
    }
};

void SectionContent::print()
{

    cout << "Content for section: " << this->sectionName << endl;

    for (auto elem : content)
    {
        //cout<< "No conversion:" << (int)elem << " ";
        cout << hex << right<< setfill('0')<< setw(2) << (int)elem << " ";
    }

    cout << endl;
}

void SectionContent::replace(int index, int size, unsigned char * content){
    for(int i = index, j=0; j < size ; i++, j++)
        content[i] = content[j];
};
