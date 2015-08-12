#include "filters.hpp"

#include <gtest/gtest.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

void cvMat2matrix(const Mat &src, Matrix &dst);
void matrix2cvMat(const Matrix &src, Mat &dst);

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

TEST_P(FiltersTest, box_filter_on_ones_mat)
{
    Matrix src(4, 4), dst(4, 4), expDst(4, 4);
    src.Ones();
    expDst.Ones();

    filters->boxFilter(src, dst);

    EXPECT_EQ(expDst, dst);
}

TEST_P(FiltersTest, box_filter_on_correct_mat)
{
    std::string input = "./testdata/image.png";
    std::string expOutput = "./testdata/image_box_filter.png";

    Mat srcMat, expDstMat;
    srcMat = imread(input, CV_LOAD_IMAGE_GRAYSCALE);
    expDstMat = imread(expOutput, CV_LOAD_IMAGE_GRAYSCALE);
    Matrix src(srcMat.rows, srcMat.cols), 
           expDst(expDstMat.rows, expDstMat.cols),
           dst(src.rows(), src.cols());
    cvMat2matrix(srcMat, src);
    cvMat2matrix(expDstMat, expDst);

    filters->boxFilter(src, dst);

    EXPECT_EQ(expDst, dst);
}

TEST_P(FiltersTest, filter2d_on_zero_mat)
{
    Matrix src(5, 5), dst(5, 5), kernel(3, 3);
    src.Zeros();
    dst.Zeros();
    kernel.Random();

    filters->filter2d(src, dst, kernel);

    EXPECT_EQ(src, dst);
}

INSTANTIATE_TEST_CASE_P(Instance,
                        FiltersTest,
                        ::testing::Range<int>((int)OPENCV, (int)NUM_IMPLS));
