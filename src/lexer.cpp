#include "../headers/lexer.h"
#include "../headers/Instruction.h"
#include "../headers/regex.h"
#include "../headers/Directive.h"
#include "../headers/ListDirective.h"
#include "../headers/SkipDirective.h"
#include "../headers/SectionDirective.h"
#include "../headers/EquDirective.h"

Directive *createDirective(string line, string label)
{
    smatch match;
    regex regex_list(list_directive);
    Directive *directive;

    if (regex_match(line, match, regex_list))
    {

        if (match.str(1) != "")
        {
            directive = new ListDirective(match.str(2), match.str(3), label);
        }
        else
        {
            directive = new ListDirective(match.str(6), match.str(7), label);
        }
    }
    else
    {
        regex regex_end(end_directive);
        if (regex_match(line, match, regex_end))
        {
            directive = new Directive(match.str(1), label);
        }

        regex regex_skip(skip_directive);
        if (regex_match(line, match, regex_skip))
        {
            directive = new SkipDirective(match.str(1), stoi(match.str(2)), label);
        }

        regex regex_equ(equ_directive);
        if (regex_match(line, match, regex_equ))
        {
            directive = new EquDirective(match.str(1), match.str(2), match.str(3), label);
        }

        regex regex_section(section_directive);
        if (regex_match(line, match, regex_section))
        {
            directive = new SectionDirective(match.str(1), match.str(2), label);
        }
    }
    directive->print();
    return directive;
};

bool match_line(string line)
{
    regex regex_directive(directive);
    regex regex_instruction(instruction);
    regex regex_label_line(label_line);
    regex regex_lonely_label(lonely_label);
    smatch match;

    //DIRECTIVE

    if (regex_match(line, match, regex_directive))
    {
        cout << "Line: " << line << " is directive" << endl
             << endl;
        Directive *directive = createDirective(line, "");
        return true;
    }

    //INSTRUCTION

    if (regex_match(line, match, regex_instruction))

    {
        cout << "Line: " << line << " is instruction" << endl
             << endl;
        Instruction *instruction = createInstruction(line, "");
        return true;
    }

    //LABEL LINE

    if (regex_match(line, match, regex_label_line))
    {
        cout << "Line: " << line << " is label line" << endl
             << endl;
        string label = match.str(2);
        string inst_or_dir = match.str(3);
        regex regex_directive(directive);
        smatch inner_match;
        Line * object;
        if(regex_match(inst_or_dir, inner_match, regex_directive)){
            object = createDirective(inst_or_dir, label);
        }
        else {
            object = createInstruction(inst_or_dir, label);
        }


        
        return true;
    }

    //LONELY LABEL

    if (regex_match(line, match, regex_lonely_label))
    {
        cout << "Line: " << line << " is lonely label" << endl
             << endl;
        Line * object = new Line(true, match.str(1), false, false);
        object->print();
        cout << endl;
        return true;
    }

    return false;
}


