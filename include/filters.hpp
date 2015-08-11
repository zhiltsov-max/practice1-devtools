#pragma once

#include "matrix.hpp"

class Filters
{
 public:
    virtual void box(const Matrix &src, Matrix& dst) = 0;
    virtual void filter2d(const Matrix &src, Matrix& dst, const Matrix &kernel) = 0;
};

static const char* filters_implementations[] = {
      "DUMMY"
    , "OPENCV"
    // , "YOUR_NAME"
};

Filters* createFilters(std::string impl);
