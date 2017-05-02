// complex mulplication by extended http://www.math.colostate.edu/~yzhou/computer/cpptutor/complex.htm

#include <iostream>
#include "Complex.h"

Complex::Complex(float realpart, float imaginarypart) {
  SetReal(realpart);
  SetImaginary(imaginarypart);
}

void Complex::SetReal(float r) {
  real = r;
}

void Complex::SetImaginary(float i) {
  imaginary = i;
}

float Complex::GetReal() const {
  return real;
}

float Complex::GetImaginary() const {
  return imaginary;
}

Complex Complex::Add(const Complex &c) const {
  return Complex(GetReal() + c.GetReal(), GetImaginary() + c.GetImaginary());
}

Complex Complex::Mul(const Complex &c) const {
  return Complex(GetReal()*c.GetReal() - GetImaginary()*c.GetImaginary()
    , GetReal()*c.GetImaginary() + GetImaginary()*c.GetReal() );
}

Complex operator+(const Complex &c1, const Complex &c2) {
  return c1.Add(c2);
}

Complex operator*(const Complex &c1, const Complex &c2) {
  return c1.Mul(c2);
}

bool operator==(const Complex &c1, const Complex &c2)
{
    return ((c1.GetReal() == c2.GetReal()) && c1.GetImaginary() == c2.GetImaginary());
}

/*
int main(void) {
  Complex x(10,9);
  Complex y(5,4);
  Complex z = x + y;
  Complex w = x * y;
  cout << z.GetReal() << '+' << z.GetImaginary() << 'i' << endl;
  cout << w.GetReal() << '*' << w.GetImaginary() << 'i' << endl;
  return 0;
}
*/