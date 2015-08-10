#pragma once

#include "matrix.hpp"

class Filters
{
 public:
    virtual void box(const Matrix &src, Matrix& dst) = 0;
    virtual void filter2d(const Matrix &src, Matrix& dst, const Matrix &kernel) = 0;
};

Filters* createFiltersOpenCV();
Filters* createFiltersDummy();

class FiltersOpenCV;
class FiltersDummy;
