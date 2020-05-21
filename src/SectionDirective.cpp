#include "../headers/SectionDirective.h"
#include "../headers/Directive.h"
#include "../headers/Assembler.h"
#include "../headers/Section.h"
#include "../headers/SymbolTable.h"

SectionDirective::SectionDirective(string name, string section, string label) : Directive(name, label)
{
    section_name = section;
};

void SectionDirective::print()
{
    Directive::print();
    cout << "Section name: " << section_name << endl
         << endl;
}

void SectionDirective::assamble()
{
    if (Assembler::currentSection != nullptr)
    {
        Assembler::currentSection->setSize(Assembler::LC);
        Assembler::LC = 0;
    }

    Assembler::currentSection = new Section(section_name);
    SymbolTable::getInstance()->addSymbol(Assembler::currentSection);
}