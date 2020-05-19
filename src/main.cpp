#include "../headers/Assembler.h"

string files[] = {"files/prog.s", "files/directive.s"};

int main(int argc, char *argv[]){
    string file_path = files[0];
    Assembler assembler(file_path);
    assembler.assamble();
};