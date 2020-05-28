#include "../headers/TNS.h"

TNS::TNS(){

};
void TNS::add(TNSRow *row){
    tns.push_back(row);
};

bool TNS::isEmpty(){
    return tns.empty();
};

void TNS::calculate(){
    
};