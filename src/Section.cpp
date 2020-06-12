#include "../headers/Section.h"
#include "../headers/Assembler.h"
#include "../headers/print.h"

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

void Section::printToFile(){
    printElementToFile(name, 25);
    if (section)
    {
        printElementToFile(section->serialNumber, 10);
    }
    else
    {
        printElementToFile("0", 10);// ako je kontsantan simbol ispisi 0 znaci da je u und sekciji
    }
    if (isDefined)
    {
        printElementToFile(size, 16);
    }
    else
    {
        printElementToFile(0, 16);// ispisi 0 ako simbol nije definisan
    }
    printElementToFile(scope, 10);
    printElementToFile(serialNumber, 20);
    Assembler::outputFile << endl;
}
