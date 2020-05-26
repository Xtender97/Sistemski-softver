#include "../headers/SkipDirective.h"

SkipDirective::SkipDirective(string name, int skipSize, string label) : Directive(name, label)
{
    numberOfBytes = skipSize;
};

void SkipDirective::print()
{
    Directive::print();
    cout << "Number of bytes: " << numberOfBytes << endl
         << endl;
}

short int SkipDirective::size()
{
    return numberOfBytes;
}

void SkipDirective::assamble()
{
    unsigned char bytes[size()];
    for (int i = 0; i < size(); i++)
    {
        bytes[size() - 1 - i] = 0x00;
    }

    Assembler::currentSection->addContent(bytes, size());
}