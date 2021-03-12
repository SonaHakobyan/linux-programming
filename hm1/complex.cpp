#include <iostream>
#include "complex.h"

ComplexNumber::ComplexNumber()
    : real(0), imag(0) {}

ComplexNumber::ComplexNumber(int r, int i)
    : real(r), imag(i) {}

int ComplexNumber::getReal() const
{
      return real;
}

int ComplexNumber::getImag() const
{
      return imag;
}

int ComplexNumber::absolute() const {
	return sqrt(real * real + imag * imag);
}

std::ostream& operator<<(std::ostream& output, const ComplexNumber& cn) {
    if (cn.getImag() == 0) {
        output << cn.getReal() << std::endl;
    }
    else if (cn.getReal() == 0) {
        output << cn.getImag() << "i" << std::endl;
    }
    else if (cn.getImag() > 0) {
        output << cn.getReal() << " + " << cn.getImag() << "i" << std::endl;
    }
    else {
        output << cn.getReal() << cn.getImag() << "i" << std::endl;
    }
    return output;
}

std::istream& operator>>(std::istream& input, ComplexNumber& cn)
{
    input >> cn.real >> cn.imag;
    return input;
}