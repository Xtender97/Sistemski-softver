#include "../headers/TNS.h"
#include "../headers/SymbolTable.h"

TNS::TNS(){

};
void TNS::add(TNSRow *row)
{
    tns.push_back(row);
};

void TNS::remove(TNSRow *row)
{
    for (int i = 0; i < tns.size(); i++)
    {
        if (row == tns[i])
        {
            tns.erase(tns.begin() + i);
            break;
        }
    }
}

bool TNS::isEmpty()
{
    return tns.empty();
};

void TNS::calculate()
{
    int numberOfCalculatedSymbols = 0;
    while (!isEmpty())
    {
        numberOfCalculatedSymbols = 0;
        for (auto elem : tns)
        {
            if (elem->canBeCalculated())
            {
                numberOfCalculatedSymbols++;
                Section *relocationSection = elem->findRelocationType();
                int value = elem->calculateExpression();
                Symbol *symbol = SymbolTable::getInstance()->getSymbol(elem->symbol);
                if (symbol != nullptr)
                {
                    symbol->isDefined = true;
                    symbol->section = relocationSection;
                    symbol->value = value;
                }
                else
                { // symbol was never used
                    symbol = new Symbol(elem->symbol, relocationSection, true, value, 'l');
                    SymbolTable::getInstance()->addSymbol(symbol);
                }
                remove(elem);
            }
        }

        if (numberOfCalculatedSymbols == 0)
        {
            string poruka = "Ima ne razresenih simbola: ";
            for(auto elem:tns){
                poruka.append(elem-> symbol+ " ");
            }
            throw poruka;
        }
    };
}