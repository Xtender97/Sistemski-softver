#include "../headers/TNSRow.h"
#include "../headers/SymbolTable.h"
#include <unordered_map>

TNSRow::TNSRow(string symbol, vector<ExpressionElem> expression)
{
    this->symbol = symbol;
    this->expression = expression;
}

int TNSRow::calculateExpression()
{
    int value = 0;
    for (auto elem : expression)
    {
        if (elem.type == LITERAL_ELEM)
        {
            if (elem.sign == MINUS)
            {
                value -= stoi(elem.value);
            }
            else
            {
                value += stoi(elem.value);
            }
        }
        else
        {
            if (elem.sign == MINUS)
            {
                value -= SymbolTable::getInstance()->getSymbol(elem.value)->value;
            }
            else
            {
                value += SymbolTable::getInstance()->getSymbol(elem.value)->value;
            }
        }
    }

    return value;
};

bool TNSRow::canBeCalculated()
{
    for (auto elem : expression)
    {
        if (elem.type == SIMBOL_ELEM)
        {
            Symbol *symbol = SymbolTable::getInstance()->getSymbol(elem.value);
            if (symbol != nullptr)
            {
                if (symbol->isDefined)
                {
                    //do nothing
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
    }
    return true;
};

// RelocationRecord * TNSRow::findRelocationType(){

//     unordered_map<string,int> classificationTable;
//     for(auto elem: expression){

//     }

// };
