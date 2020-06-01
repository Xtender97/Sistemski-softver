#include "../headers/Assembler.h"

string files[] = {"files/prog.s", "files/directive.s", "files/smalltest.s", "files/veljatest.s"};

int main(int argc, char *argv[]){
    string file_path;
    if (argc == 1 ){
        file_path = files[2];
        cout << "argc == 0" << endl;
    }
    else {
        file_path = argv[1];
        cout << "argc != 0" << endl;

    }
    
    Assembler assembler(file_path);
    assembler.assamble();
};