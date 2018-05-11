#ifndef INCLUDED_BS_
#define INCLUDED_BS_

#include <vector>
#include <algorithm>

/*
 * This file contains useful functions that will be used
 * throughout the project
 */

namespace bs
{
    /*
     * Function that will return a vector of size 'size' from 'begin' to 'end'.
     */
    std::vector<double> seq_length(double const begin, double const end, int const size)
    {
        std::vector<double> seq(size, 0);

        seq[0] = begin;
        for (size_t idx = 1; idx != (size-1); ++idx)
            seq[idx] = begin + idx * ((end - begin) / size);
        seq[size-1] = end;
        
        return seq;
    }

    /*
     * Calculate the span of two vectors
     * 
     * TODO check if O(n) is fastest for obtaining differnence vector... I think so
     */ 
    double span(vector<double> const &first, vector<double> const &second)
    {  
        size_t length = first.size()
        
        if (length != second.size())
            throw string("Error: vectors do not have same length (bs::span(first, second))");

        std::vector<double> diff(length, 0);
        for (size_t idx = 0; idx != length; ++idx)
            diff[idx] = first[idx] - second[idx];
        
        auto result = std::minmax_element(diff.begin(), diff.end());

        return result.second - result.first;
    }
}


#endif