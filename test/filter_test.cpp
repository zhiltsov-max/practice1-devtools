#include <gtest/gtest.h>
#include "matrix.hpp"
#include "filter.h"

TEST(practice1, filter_test)
{
    Matrix m(3, 3), kernel(2, 2);
    m.Zeros();
    Matrix mf = filter2d(m, kernel);

    EXPECT_EQ(m, mf);
}
