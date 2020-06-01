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
    for (int i = 0; i <= size - 1; i++)
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
        cout << hex << right << setfill('0') << setw(2) << (int)elem << " ";
    }

    cout << endl;
}

void SectionContent::replace(int index, int size, short int replacement)
{

    short int currentValue = 0;
    for (int i = index; i < size+index; i++)
    {
        currentValue |= (content[i] << (i - index) * 8);
    }

    // cout << "Trenutna vrednost tokom: " << currentValue << endl;

    replacement += currentValue;

    //cout << "Vrednost sa kojom menjam " << replacement << endl;

    unsigned char bytes[size];
    for (int i = 0; i < size; i++)
    {
        bytes[i] = (replacement >> (i * 8)); //rotated to little endian here
    }

    for (int i = index, j = 0; j < size; i++, j++)
        content[i] = bytes[j];
};
