#pragma once

#include <time.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

typedef unsigned char uchar;

class Matrix
{
private:
    uchar **values;
public:
    int kRows, kCols;
public:
    Matrix() {};
    Matrix(int _kRows, int _kCols);
    void Zeros();
    void Ones();    
    void Random(int _seed = 10);
    uchar *operator[](int i) const { return values[i]; }
    bool operator==(const Matrix& m) const;
    friend ostream& operator<<(ostream& os, const Matrix& m);
    ~Matrix();
};
