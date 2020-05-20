#pragma once
#include <iostream>
#include <iomanip>

template <typename T>
void printElement(T t, const int &width)
{
    char separator = ' ';
    std::cout << left << std::setw(width) << std::setfill(separator) << t;
}