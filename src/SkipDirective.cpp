#include "../headers/SkipDirective.h"


SkipDirective::SkipDirective(string name, int skipSize, string label): Directive( name, label){
    numberOfBytes = skipSize;
};


void SkipDirective::print(){
    Directive::print();
    cout << "Number of bytes: " << numberOfBytes << endl << endl;
}

short int SkipDirective::size(){
    return numberOfBytes;
}