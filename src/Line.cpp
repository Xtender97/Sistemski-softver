#include "../headers/Line.h"

Line::Line(bool hasLabel, string label, bool isDirective, bool isInstruction)
{
    m_hasLabel = hasLabel;
    m_label = label;
    m_isDirective = isDirective;
    m_isInstruction = isInstruction;
};

void Line::print()
{
    if (m_hasLabel)
    {
        cout << "Label: " << m_label << endl;
    };
}
