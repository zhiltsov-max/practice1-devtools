#include "filters.hpp"

#include <gtest/gtest.h>

class FiltersTest : public ::testing::TestWithParam<int>
{
 public:
    virtual void SetUp()
    {
        filters = createFilters(static_cast<FILTERS_IMPLEMENTATIONS>(GetParam()));
    }
    virtual void TearDown()
    {
        delete filters;
    }

    Filters* filters;
};

TEST_P(FiltersTest, box_filter_on_zero_mat)
{
    Matrix src(5, 5), dst(5, 5), dstExp(5, 5);
    src.Zeros();
    dstExp.Zeros();

    filters->boxFilter(src, dst);

    EXPECT_EQ(dstExp, dst);
}

TEST_P(FiltersTest, filter2d)
{
    Matrix src(5, 5);
    src.Zeros();
    Matrix dst(5, 5);
    Matrix kernel(3, 3);

    filters->filter2d(src, dst, kernel);

    EXPECT_EQ(src, dst);
}

INSTANTIATE_TEST_CASE_P(Instance,
                        FiltersTest,
                        ::testing::Range<int>((int)OPENCV, (int)NUM_IMPLS));
