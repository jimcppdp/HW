class Complex {
public:
    Complex(float realpart = 0, float imaginarypart = 0);
    Complex Add(const Complex &c) const;
    Complex Mul(const Complex &c) const;
    float GetReal() const;
    float GetImaginary() const;
    void SetReal(float r);
    void SetImaginary(float i);
private:
    float real;
    float imaginary;
};

Complex operator+(const Complex &c1, const Complex &c2);
Complex operator*(const Complex &c1, const Complex &c2);
bool operator==(const Complex &c1, const Complex &c2);