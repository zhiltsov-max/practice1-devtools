#include "filters.hpp"

Filters* createFiltersDummy();
Filters* createFiltersOpenCV();

Filters* createFilters(std::string impl)
{
    if (impl == "DUMMY")
    {
        return createFiltersDummy();
    }
    else if (impl == "OPENCV")
    {
        return createFiltersOpenCV();
    }
    else
    {
        return 0;
    }
}
