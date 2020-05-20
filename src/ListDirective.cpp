#include "../headers/ListDirective.h"
#include <iostream>
#include "../headers/Directive.h"
#include "../headers/regex.h"
#include <regex>
#include "../headers/Enums.h"

using namespace std;

ListDirective::ListDirective(string name, string list, string label) : Directive(name, label)
{

    regex regex_elem(simbol + "|" + literal);

    //cout << simbol + "|" + literal << endl;

    regex regex_simbol(simbol);
    regex regex_literal(literal);

    smatch match;

    while (regex_search(list, match, regex_elem))
    {
        string elem = match.str();
        // cout << match.str() << endl;
        // cout << "Elemnt:" << elem << endl;
        smatch match_inner;
        if (regex_match(elem, match_inner, regex_simbol))
        {
            //cout << "Simbol" << endl;
            Elem e = {SIMBOL_ELEM, elem};
            directive_list.push_back(e);
        }
        else
        {
            //cout << "Literal" << endl;

            Elem e = {LITERAL_ELEM, elem};
            directive_list.push_back(e);
        }

        list = match.suffix();
    };
}

void ListDirective::print()
{
    Directive::print();
    int i = 0;

    for (auto elem : directive_list)
    {
        i++;
        cout << "Element " << i << ". : " << elem.value << " of type " << (elem.type? "SIMBOL":"LITERAL") << endl;
    };

    cout << endl;
};

short int ListDirective::size(){
    int multiplier = 0;
    if( type == WORD_DIRECTIVE){
        multiplier = 2;
    };
    if( type == BYTE_DIRECTIVE){
        multiplier = 1;
    };

    return directive_list.size()*multiplier;
}