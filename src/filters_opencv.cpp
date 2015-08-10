#include "filters.hpp"

class FiltersOpenCV : public Filters
{
 public:
    virtual void box(const Matrix &src, Matrix& dst)
    {
        dst.Zeros();
    }
    virtual void filter2d(const Matrix &src, Matrix& dst, const Matrix &kernel)
    {
        dst.Zeros();
    }
};

Filters* createFiltersOpenCV()
{
    Filters* filters = new FiltersOpenCV();
    return filters;
}
