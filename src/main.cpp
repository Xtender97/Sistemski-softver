#include "../headers/Assembler.h"

string files[] = {"files/prog.s", "files/directive.s", "files/smalltest.s"};

int main(int argc, char *argv[]){
    string file_path = files[2];
    Assembler assembler(file_path);
    assembler.assamble();
};