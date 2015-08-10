#include "matrix.hpp"
#include "filter.h"

using namespace std;

int main()
{
    cout << "---------------------------" << endl;

    Matrix m(3, 4);
    m.Random();
    cout << m;

    cout << "---------------------------" << endl;

    Matrix kernel(2, 2);
    Matrix mf = filter2d(m, kernel);
    cout << mf;

    cout << "---------------------------" << endl;

    return 0;
}
