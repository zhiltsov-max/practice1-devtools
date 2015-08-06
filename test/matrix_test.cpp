#include <gtest/gtest.h>
#include "matrix.hpp"

TEST(practice1, matrix_set_zeros)
{
    Matrix m(2, 2);
    m.Zeros();

    EXPECT_EQ(0, m[0][0]);
    EXPECT_EQ(0, m[0][1]);
    EXPECT_EQ(0, m[1][0]);
    EXPECT_EQ(0, m[1][1]);
}