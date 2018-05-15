#ifndef INCLUDED_BS_
#define INCLUDED_BS_

#include <vector>
#include <algorithm>
#include <iostream>

/*
 * This file contains useful functions that will be used
 * throughout the project
 */

namespace bs
{
    std::vector<double> seq_length(double const begin, double const end, int const size);
    double              span(std::vector<double> const &first, std::vector<double> const &second);
    size_t              min_sum(std::vector<double> const &data, double const minSum);
}

#endif