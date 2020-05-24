#include "../headers/Directive.h"
#include "../headers/Line.h"
#include "../headers/Assembler.h"

unordered_map<string, DirectiveType> Directive::DirectiveTypesMap = {
    {"skip", SKIP},
    {"end", END}, //0
    {"global", GLOBAL},
    {"extern", EXTERN},
    {"section", SECTION},
    {"byte", BYTE_DIRECTIVE},
    {"word", WORD_DIRECTIVE},
    {"equ", EQU}
};



Directive::Directive(string name, string label) : Line(!label.empty(), label, true, false)
{
    directive_name = name;
    type = DirectiveTypesMap[name];
};

void Directive::print(){
    Line::print();
    cout << "Directive type: " << directive_name << endl;
};

short int Directive::size(){
    return 0;
}
void Directive::assamble(){
    if(directive_name == "end"){
        Assembler::run = false;
    }
}