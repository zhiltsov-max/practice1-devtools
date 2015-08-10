#include "filters.hpp"

class FiltersDummy : public Filters
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

Filters* createFiltersDummy()
{
    Filters* filters = new FiltersDummy();
    return filters;
}
