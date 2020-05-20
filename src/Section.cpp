#include "../headers/Section.h"


Section::Section(string n, int section_serail, bool definition, int val, char global_or_local, int serialNumber)
    :Symbol(n, section_serail, definition, val, global_or_local, serialNumber)
{
    size = 0;
}


void Section::setSize(int size){
    this->size = size;
}