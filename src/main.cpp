#include "../headers/Assembler.h"

string files[] = {"files/prog.s", "files/directive.s", "files/smalltest.s", "files/veljatest.s"};

int main(int argc, char *argv[])
{
    string file_path;
    string output_file_path;


    
    if (argc == 4)
    {
    
        for (int i = 1; i < argc; i++)
        {
            string arg = argv[i];
            if (arg == "-o")
            {
                output_file_path = argv[++i]; //skip next one
            }
            else
            {
                file_path = argv[i];
                cout << file_path << endl;
            };
        };

        Assembler assembler(file_path, output_file_path);
        assembler.assamble();
    }
    else
    {
        cout << "Expected 2 arguments! Example 'input_file.s -o output_file.txt' " << endl;
    }
};