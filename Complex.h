#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <fstream>

using namespace std;

template<class T>
class Complex {

public:

    Complex();

    Complex(T re, T im);

    Complex(const Complex<T> &other);

    Complex(char *filename);

    const Complex<T> operator+(const Complex<T> &other);

    const Complex<T> operator-(const Complex<T> &other);

    const Complex<T> operator*(const Complex<T> &other);

    Complex<T> &operator+=(const Complex<T> &other);

    Complex<T> &operator-=(const Complex<T> &other);

    Complex<T> &operator*=(const Complex<T> &other);

    Complex<T> &operator=(const Complex<T> &other);

    template<class U>
    friend ostream &operator<<(ostream &os, const Complex<U> &complex);

    template<class U>
    friend istream &operator>>(istream &is, Complex<U> &complex);

    ~Complex();


    // static

    static Complex<T> **read_matrix(const char *filename, size_t *rows, size_t *columns);

private:
    T re, im;
};


template<class T>
Complex<T>::Complex() {
    re = im = T();
}


template<class T>
Complex<T>::~Complex() {}

template<class T>
Complex<T>::Complex(T re, T im) {
    this->re = re;
    this->im = im;
}


template<class T>
Complex<T>::Complex(char *filename) {

    ifstream is;
    is.open(filename);

    if (!is.is_open()) {
        is.close();
        cerr << "Can't open file: " << filename << endl;
    }

    operator>>(is, *this);

    is.close();
}

template<class T>
Complex<T>::Complex(const Complex<T> &other) {
    this->re = other.re;
    this->im = other.im;
}


template<class U>
istream &operator>>(istream &is, Complex<U> &complex) {

    is >> complex.re;
    is >> complex.im;

    return is;
}


template<class U>
ostream &operator<<(ostream &os, const Complex<U> &complex) {
    os << "( Re: " << complex.re << ", Im: " << complex.im << " )";
    return os;
}

// NOTE: returns new Complex object
template<class T>
const Complex<T> Complex<T>::operator+(const Complex<T> &other) {
    Complex<T> result(*this);
    result += other;
    return result;
}

// NOTE: returns new Complex object
template<class T>
const Complex<T> Complex<T>::operator-(const Complex<T> &other) {
    Complex<T> result(*this);
    result -= other;
    return result;
}


// NOTE: returns new Complex object
template<class T>
const Complex<T> Complex<T>::operator*(const Complex<T> &other) {
    Complex<T> result(*this);
    result *= other;
    return result;
}


template<class T>
Complex<T> &Complex<T>::operator+=(const Complex<T> &other) {
    this->re += other.re;
    this->im += other.im;
    return *this;
}

template<class T>
Complex<T> &Complex<T>::operator-=(const Complex<T> &other) {
    this->re -= other.re;
    this->im -= other.im;
    return *this;
}


template<class T>
Complex<T> &Complex<T>::operator*=(const Complex<T> &other) {
    this->re = this->re * other.re - this->im * other.im;
    this->im = this->re * other.im + this->im * other.re;
    return *this;
}


template<class T>
Complex<T> &Complex<T>::operator=(const Complex<T> &other) {

    if (this != &other) {
        this->~Complex(); // invoke destructor
        new(this) Complex(other); // placement new
    }

    return *this;
}

template<class T>
Complex<T> **Complex<T>::read_matrix(const char *filename, size_t *rows, size_t *columns) {
    if (!filename) {
        cerr << "Filename shouldn't be null" << endl;
        return nullptr;
    }
    if (!rows || !columns) {
        cerr << "Invalid rows and columns null pointers" << endl;
        return nullptr;
    }


    ifstream is;
    is.open(filename);

    if (!is.is_open()) {
        cerr << "Can't open file: " << filename << endl;
        return nullptr;
    }

    is >> *rows;
    is >> *columns;

    Complex<T> **data = new Complex<T> *[*rows];

    for (int i = 0; i < *rows; ++i) {
        data[i] = new Complex<T>[*columns];
    }

    // initialize data
    for (int i = 0; i < *rows; ++i) {
        for (int j = 0; j < *columns; ++j) {
            data[i][j] = Complex();
        }
    }

    T real, imaginary;

    for (int i = 0; i < *rows; ++i) {
        for (int j = 0; j < *columns; ++j) {
            is >> real;
            is >> imaginary;

            data[i][j] = Complex(real, imaginary);
        }
    }

    is.close();

    return data;
}

#endif // COMPLEX_H