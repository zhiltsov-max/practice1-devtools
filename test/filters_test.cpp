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

TEST_P(FiltersTest, box)
{
    Matrix src(5, 5);
    src.Zeros();

    Matrix dst(5, 5);

    filters->box(src, dst);

    EXPECT_EQ(src, dst);
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
