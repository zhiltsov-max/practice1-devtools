#pragma once

#include "matrix.hpp"

class Filters
{
 public:
    virtual void box(const Matrix &src, Matrix& dst) = 0;
    virtual void filter2d(const Matrix &src, Matrix& dst, const Matrix &kernel) = 0;
};

enum FILTERS_IMPLEMENTATIONS {
    OPENCV,
    // Add your enum value here
    // YOUR_NAME,
    NUM_IMPLS
};

Filters* createFilters(FILTERS_IMPLEMENTATIONS impl);
