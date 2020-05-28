#include "../headers/TNSRow.h"
#include "../headers/SymbolTable.h"

TNSRow::TNSRow(string symbol, vector<ExpressionElem> expression)
{
    this->symbol = symbol;
    this->expression = expression;
}

int TNSRow::calculateExpression(){

};

bool TNSRow::canBeCalculated(){
    for(auto elem: expression){
        if(elem.type == SIMBOL_ELEM){
            Symbol* symbol =  SymbolTable::getInstance()->getSymbol(elem.value);
            if(symbol != nullptr){
                if(symbol->isDefined){


                    

                }else{
                    return false;
                }
            }
            else{
                return false;
            }
        }
    }
};

