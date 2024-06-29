//umanskyvivian@gmail.com
#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <QString>
#include <iostream>
#include <cmath>

class Complex {
private:
    double real;
    double imag;

public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    double get_real() const {
        return real;
    }

    double get_imag() const {
        return imag;
    }

    double magnitude() const {
        return std::sqrt(real * real + imag * imag);
    }

    bool operator>(const Complex& other) const {
        return magnitude() > other.magnitude();
    }

    bool operator<(const Complex& other) const {
        return magnitude() < other.magnitude();
    }

    bool operator==(const Complex& other) const {
        return real == other.real && imag == other.imag;
    }

    QString toQString() const {
        return QString("%1 + %2i").arg(real).arg(imag);
    }

    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c.real;
        if (c.imag >= 0) os << '+';
        os << c.imag << 'i';
        return os;
    }
};

#endif // COMPLEX_HPP
