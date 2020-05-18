#include "../headers/EquDirective.h"
#include <regex>
#include "../headers/regex.h"

EquDirective::EquDirective(string name, string equ_simbol, string expr, string label) : Directive(name, label)
{
    simbol_name = simbol;
    regex regex_expression("(\\+|-)?\\s?(" + simbol + "|" + literal + ")\\s?");
    smatch match;
    while (regex_search(expr, match, regex_expression))
    {
        string elem = match.str(2);
        Sign sign = match.str(1) == "-" ? MINUS : PLUS;
        ListType type;
        smatch inner_match;
        regex regex_simbol(simbol);
        if (regex_match(elem, inner_match, regex_simbol))
        {
            type = SIMBOL_ELEM;
        }
        else
        {
            type = LITERAL_ELEM;
        }
        ExpressionElem exp = {sign,type, elem};
        expression_list.push_back(exp);
        expr = match.suffix();
    }
};

void EquDirective::print(){
    Directive::print();
    int i = 0;

    for (auto elem : expression_list)
    {
        i++;
        cout << "Element " << i << ". : " << elem.value << " of type " << (elem.type? "SIMBOL":"LITERAL") << " with sign: " << (elem.sign? "MINUS":"PLUS") <<  endl;
    };

    cout << endl;
}