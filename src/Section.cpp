#include "../headers/Section.h"

Section::Section(string n, bool definition, int val, char global_or_local, int serialNumber)
    : Symbol("." + n, this, definition, val, global_or_local, serialNumber)
{
    size = 0;
    relocationTable = new RelocationTable(n);
    content = new SectionContent(n);
}

Section::Section(string name) : Symbol("." + name, this, true, 0, 'l')
{
    size = 0;
    relocationTable = new RelocationTable(name);
    content = new SectionContent(name);
}

void Section::setSize(int size)
{
    this->size = size;
}

void Section::addRelocation(RelocationRecord *relocation)
{
    relocationTable->addRelocation(relocation);
};

void Section::addContent(unsigned char *content, int size)
{
    this->content->append(content, size);
}

void Section::setSerialNumber(int serial)
{
    serialNumber = serial;
    
};
