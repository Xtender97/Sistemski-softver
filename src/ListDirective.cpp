#include "../headers/ListDirective.h"
#include <iostream>
#include "../headers/Directive.h"
#include "../headers/regex.h"
#include <regex>
#include "../headers/Enums.h"

using namespace std;

ListDirective::ListDirective(string name, string list, string label):Directive(name, label){

    regex regex_elem(simbol +"|" + literal);

    regex regex_simbol(simbol);
    regex regex_literal(literal);

    smatch match;

    regex_search(list, match, regex_elem);

    for (string elem: match){
        smatch match_inner;
        if (regex_match(elem, match_inner,regex_simbol)){
            Elem e = {SIMBOL_ELEM, elem};
            directive_list.push_back(e);
        }
        else {
            Elem e = {LITERAL_ELEM, elem};
            directive_list.push_back(e);
        }
    }


}