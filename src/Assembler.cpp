#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include "../headers/lexer.h"

using namespace std;
string files []= {"files/prog.s", "files/directive.s"};

int main(int argc, char *argv[])
{
    bool status = true;

    ifstream file(files[0]);
    string line;
    int line_count = 0;
    while (getline(file, line))
    {
        line_count++;
        line = regex_replace(line, regex("^\\s+"), "");
        if (line == "")
            continue;
        if (!match_line(line))
        {
            status = false;
            cout << "Error at line: " << line_count << endl;
            cout << line << endl
                 << endl;
            break;
        }
    }

    cout << "Exited with status " << status << endl;

    return 1;
    // string text[] = {"*literal", "literal", "$literal", "/literal", "(%r5)", "%r5", "*%r5", "*(%r5)", "*literal(%r3)", "literal(%pc)", "$literal(%r3)", "/literal(%r3)", "*a(%r)", "b(r5)", "a(pc)", "asd(%r0)"};
    // string text_double[] = {"*literal(%r3)", "literal(%pc)", "$literal(%r3)", "/literal(%r3)", "*a(%r)", "b(r5)", "a(pc)", "asd(%r0)"};

    // string lines[] = {
    //     "int *SIMBOL(%pc) ",
    //     "int *55(%pc)    ",
    //     "int *55(%r7)  ",
    //     "int *55(%r6)",
    //     "int *sim(%r6)",
    //     "int 55",
    //     "int *55  ",
    //     "call simbol",
    //     "jmp *%r4",
    //     "jgt *(%r8)",
    //     "jgt *(%r7)",
    //     "jne $sda"

    // };

    // string doubleOperand[] = {
    //     "mov %r5, %r3",
    //     "add 44, %r5",
    //     "sub $simbol, simbol2",
    //     "mul simbol, %(r4)",
    //     "div $5, %pc",
    //     "div $1231, (%pc)",
    //     "xchg 123, simbol(%pc)",
    //     "xchg 123, 4(%pc)",
    //     "xor 5%r5, a(r4)",
    //     "xor 5(%r5), a(r4)",

    // };

    // for (int i = 0; i < 10; i++)
    // {
    //     match_line(doubleOperand[i]);
    // }
}