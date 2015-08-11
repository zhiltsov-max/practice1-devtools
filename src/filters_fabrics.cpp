#include "filters.hpp"

bool isKnownImplementation(std::string impl);

Filters* createFiltersDummy();
Filters* createFiltersOpenCV();
// Declare your implementation here
// Filters* createFiltersYourName();

Filters* createFilters(std::string impl)
{
    if (!isKnownImplementation(impl))
        return 0;

    if (impl == "DUMMY")
    {
        return createFiltersDummy();
    }
    else if (impl == "OPENCV")
    {
        return createFiltersOpenCV();
    }
    // Call your method here
    // else if (impl == "YOUR_NAME")
    // {
    //     return createFiltersYourName();
    // }
    else
    {
        return 0;
    }
}

bool isKnownImplementation(std::string impl)
{
    for (int i = 0; filters_implementations[i][0] != ' '; i++)
    {
        if (impl == std::string(filters_implementations[i]))
            return true;
    }

    return false;
}
