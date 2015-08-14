#include "filters.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

void matrix2cvMat(const Matrix &src, Mat &dst);
void cvMat2matrix(const Mat &src, Matrix &dst);

class FiltersOpenCV : public Filters
{
 public:
    virtual void boxFilter(const Matrix &src, Matrix& dst, const int kSize = 3)
    {
        Mat srcMat, dstMat;
        matrix2cvMat(src, srcMat);
        cv::boxFilter(srcMat, dstMat, -1, Size(kSize, kSize));
        cvMat2matrix(dstMat, dst);
    }

    virtual void filter2d(const Matrix &src, Matrix& dst, const Matrix &kernel)
    {
        Mat srcMat, dstMat, kernelMat;
        matrix2cvMat(src, srcMat);
        matrix2cvMat(kernel, kernelMat);
        cv::filter2D(srcMat, dstMat, -1, kernelMat,
            Point(-1, -1), 0.0, BORDER_CONSTANT);
        cvMat2matrix(dstMat, dst);
    }

    virtual void median(const Matrix &src, Matrix &dst,
        const int kSize = 3)
    {
        Mat srcMat, dstMat;
        matrix2cvMat(src, srcMat);
        cv::medianBlur(srcMat, dstMat, kSize);
        cvMat2matrix(dstMat, dst);
    }

    virtual void SobelOx(const Matrix &src, Matrix &dst)
    {
        Mat srcMat, dstMat;
        matrix2cvMat(src, srcMat);
        cv::Sobel(srcMat, dstMat, -1, 1, 0);
        cvMat2matrix(dstMat, dst);
    }

private:
    friend void matrix2cvMat(const Matrix &src, Mat &dst);
    friend void cvMat2matrix(const Mat &src, Matrix &dst);
};

void matrix2cvMat(const Matrix &src, Mat &dst)
{
    dst.create(src.rows(), src.cols(), CV_8UC1);
    uchar *p;
    for (int i = 0; i < src.rows(); i++)
    {
        p = dst.ptr<uchar>(i);
        for (int j = 0; j < src.cols(); j++)
        {
            p[j] = src[i][j];
        }
    }
}

void cvMat2matrix(const Mat &src, Matrix &dst)
{
    if (dst.data() == 0 ||
        src.rows != dst.rows() || src.cols != dst.cols())
    {
        return;
    }
    const uchar *p;
    for (int i = 0; i < src.rows; i++)
    {
        p = src.ptr<uchar>(i);
        for (int j = 0; j < src.cols; j++)
        {
            dst[i][j] = p[j];
        }
    }
}

Filters* createFiltersOpenCV()
{
    Filters* filters = new FiltersOpenCV();
    return filters;
}
