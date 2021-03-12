#include <iostream>
#include <vector>
#include "complex.h"

/// <summary>
/// Sorts complex numbers by absolute values
/// </summary>
/// <param name="vector"></param>
void sorting(std::vector<ComplexNumber>& vector)
{
    for(int i = 0; i < static_cast<int>(vector.size() - 1); ++i)
    {
        for(int j = 0; j < static_cast<int>(vector.size() - i - 1); ++j)
        {
            if(vector[j].absolute() > vector[j + 1].absolute())
            {
                std::swap(vector[j], vector[j + 1]);
            }
        }
    }
}

int main()
{
    std::cout << "Size: ";
    int size;
    std::cin >> size;

    std::vector<ComplexNumber> buffer;

    for (int i = 0; i < size; ++i)
    {
        std::cout << "Number: ";
        ComplexNumber cn;
        std::cin >> cn;
        
        buffer.push_back(cn);
    }

    sorting(buffer);

    for (int i = 0; i < size; ++i)
    {
        std::cout << buffer[i];
    }

    std::cin >> size;
}