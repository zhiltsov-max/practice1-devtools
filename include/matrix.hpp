#pragma once

#include <iostream>

typedef unsigned char uchar;

class Matrix
{
 public:
    Matrix(int rows, int cols);
    Matrix(const Matrix& m);
    ~Matrix();

    int rows() const;
    int cols() const;
    uchar** data() const;
    bool operator==(const Matrix& m) const;
    Matrix& operator=(const Matrix& m);
    uchar* operator[](int i) const;

    // Initialization methods
    void Zeros();
    void Ones();
    void Random(int seed = 1);

    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);

 private:
     void alloc(int rows, int cols);
     void free();
     void copy(const Matrix& m);

    uchar** values;
    int kRows, kCols;
};
