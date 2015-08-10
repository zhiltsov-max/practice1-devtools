#include "filters.hpp"

#include <gtest/gtest.h>

TEST(FiltersDummy, box_dummy)
{
    Matrix src(5, 5);
    src.Zeros();

    Matrix dst(5, 5);
    Filters* filters = createFiltersDummy();

    filters->box(src, dst);

    EXPECT_EQ(src, dst);
}

TEST(FiltersDummy, box_opencv)
{
    Matrix src(5, 5);
    src.Zeros();

    Matrix dst(5, 5);
    Filters* filters = createFiltersOpenCV();

    filters->box(src, dst);

    EXPECT_EQ(src, dst);
}

// EXPERIMENTS WITH TYPED TESTS

// #include <list>
// using namespace std;

// template <typename T>
// class FiltersTest : public ::testing::Test
// {
//  public:
//   // T value_;
// };

// typedef ::testing::Types<FiltersDummy, FiltersOpenCV> MyTypes;
// TYPED_TEST_CASE(FiltersTest, MyTypes);

// TYPED_TEST(FiltersTest, DoesBlah)
// {
//   // TypeParam n = this->value_;
//   // EXPECT_EQ(0, n);

//     Matrix src(5, 5);
//     src.Zeros();

//     Matrix dst(5, 5);
//     Filters* filters = new TypeParam();

//     filters->box(src, dst);

//     EXPECT_EQ(src, dst);
// }
