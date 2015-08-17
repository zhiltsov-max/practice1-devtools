#include "filters.hpp"

Filters* createFiltersOpenCV();
Filters* createFiltersZhiltsov();

Filters* createFilters(FILTERS_IMPLEMENTATIONS impl)
{
    switch (impl) {
        case OPENCV:
            return createFiltersOpenCV();
		case ZHILTSOV:
			return createFiltersZhiltsov();
        default:
            return 0;
    }
}
