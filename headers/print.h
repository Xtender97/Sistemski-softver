#pragma once
#include <iostream>
#include <iomanip>
#include "Assembler.h"

template <typename T>
void printElement(T t, const int &width)
{
    char separator = ' ';
    std::cout << left << std::setw(width) << std::setfill(separator) << t;
}

template <typename T>
void printElementToFile(T t, const int &width)
{
    char separator = ' ';
    Assembler::outputFile << left << std::setw(width) << std::setfill(separator) << t;
}