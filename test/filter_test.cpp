#include <gtest/gtest.h>
#include "matrix.hpp"
#include "filter.h"

TEST(filter, filter_test)
{
    Matrix m(3, 3);
    m.Zeros();

    Matrix kernel(2, 2);
    Matrix mf = filter2d(m, kernel);

    EXPECT_EQ(m, mf);
}
