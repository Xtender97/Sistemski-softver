#include "../headers/lexer.h"
#include "../headers/Instruction.h"
#include "../headers/regex.h"

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
        return true;
    }

    //INSTRUCTION

    if (regex_match(line, match, regex_instruction))

    {
        cout << "Line: " << line << " is instruction" << endl
             << endl;
        Instruction* instruction = createInstruction(line);
        return true;
    }

    //LABEL LINE

    if (regex_match(line, match, regex_label_line))
    {
        cout << "Line: " << line << " is label line" << endl
             << endl;
        return true;
    }

    //LONELY LABEL

    if (regex_match(line, match, regex_lonely_label))
    {
        cout << "Line: " << line << " is lonely label" << endl
             << endl;
        return true;
    }

    cout << "Error at line: " << line << endl
         << endl;
    return false;
}

// cout << "First capture group: " << match.str(1) << endl;
// cout << "Second capture group: " << match.str(2) << endl;
// cout << "Third capture group: " << match.str(3) << endl;
// cout << "Fourth capture group: " << match.str(4) << endl;
// cout << "Fifth capture group: " << match.str(5) << endl;
// cout << "Sixth capture group: " << match.str(6) << endl
//      << endl;