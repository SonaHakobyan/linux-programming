#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

/// <summary>
/// Represents complex number
/// </summary>
class ComplexNumber
{

private:

	/// <summary>
	/// The real part
	/// </summary>
	int real;

	/// <summary>
	/// The imaginary part
	/// </summary>
	int imag;

public:

    /// <summary>
	/// Init complex number
	/// </summary>
	ComplexNumber();

	/// <summary>
	/// Init complex number
	/// </summary>
	/// <param name="r"></param>
	/// <param name="i"></param>
	ComplexNumber(int r, int i);

    /// <summary>
	/// Get real part
	/// </summary>
    int getReal() const;

    /// <summary>
	/// Get imaginary part
	/// </summary>
    int getImag() const;

	/// <summary>
	/// Calculates absolute value
	/// </summary>
	/// <returns></returns>
	int absolute() const;

	/// <summary>
	/// Print complex number
	/// </summary>
    friend std::ostream& operator<<(std::ostream& output, const ComplexNumber& cn);

    /// <summary>
	/// Read complex number
	/// </summary>
    friend std::istream& operator>>(std::istream& input, ComplexNumber& cn);

    /// <summary>
	/// Adds two complex numbers
	/// </summary>
	/// <param name="lhs"></param>
    /// <param name="rhs"></param>
	/// <returns></returns>
    friend ComplexNumber operator+(ComplexNumber lhs, const ComplexNumber& rhs)
    {
        lhs.real += rhs.real;
        lhs.imag += rhs.imag;

        return lhs; 
    }

    /// <summary>
	/// Substracts two complex numbers
	/// </summary>
	/// <param name="lhs"></param>
    /// <param name="rhs"></param>
	/// <returns></returns>
    friend ComplexNumber operator-(ComplexNumber lhs, const ComplexNumber& rhs)
    {
        lhs.real -= rhs.real;
        lhs.imag -= rhs.imag;

        return lhs; 
    }

    /// <summary>
	/// Multiplies two complex numbers
	/// </summary>
	/// <param name="lhs"></param>
    /// <param name="scalar"></param>
	/// <returns></returns>
    friend ComplexNumber operator*(ComplexNumber lhs, const int scalar)
    {
        lhs.real *= scalar;
        lhs.imag *= scalar;

        return lhs; 
    }
};