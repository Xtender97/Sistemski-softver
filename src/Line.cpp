#include "../headers/Line.h"

Line::Line(bool hasLabel, string label, bool isDirective, bool isInstruction)
{
    this->hasLabel = hasLabel;
    this->label = label;
    this->isDirective = isDirective;
    this->isInstruction = isInstruction;
};

void Line::print()
{
    if (hasLabel)
    {
        cout << "Label: " << label << endl;
    };
}
 short int Line::size(){
     return 0;
 }

 void Line::assamble(){
     cout << "ass" << endl;
 };
