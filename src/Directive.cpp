#include "../headers/Directive.h"
#include "../headers/Line.h"

unordered_map<string, DirectiveType> Directive::DirectiveTypesMap = {
    {"skip", SKIP},
    {"end", END},
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

void  Directive::print(){
    cout << "Directive type: " << directive_name << endl << endl;
};