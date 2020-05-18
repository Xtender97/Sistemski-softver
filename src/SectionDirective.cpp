#include "../headers/SectionDirective.h"
#include "../headers/Directive.h"


SectionDirective::SectionDirective(string name, string section, string label) : Directive(name, label){
    section_name = section;
};


void SectionDirective::print(){
    Directive::print();
    cout << "Section name: " << section_name << endl << endl;

}