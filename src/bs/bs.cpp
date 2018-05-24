#include "bs.h"

#include <algorithm>
#include <functional>
#include <iostream>

using namespace std;

namespace bs
{
    /*
     * Function that will return a vector of size 'size' from 'begin' to 'end'.
     */
    vector<double> seq_length(double const begin, double const end, int const size)
    {
        vector<double> seq(size, 0);

        seq[0] = begin;
        for (int idx = 1; idx != (size-1); ++idx)
            seq[idx] = begin + idx * ((end - begin) / size);
        seq[size-1] = end;
        
        return seq;
    }

    /*
     * Calculate the span of two vectors
     * 
     * TODO check if O(n) is fastest for obtaining difference vector... I think so
     */ 
    double span(vector<double> const &first, vector<double> const &second)
    {  
        size_t length = first.size();
        
        if (length != second.size())
            throw string("Error: vectors do not have same length (bs::span(first, second))");

        vector<double> diff(length, 0);
        for (size_t idx = 0; idx != length; ++idx)
            diff[idx] = first[idx] - second[idx];
        
        auto result = minmax_element(begin(diff), end(diff));

        return *result.second - *result.first;
    }

    /*
     * Return the first element such that the sum of all
     * elements till this element is at least 'value'.
     * 
     * Return size of 'data' vector if sum is smaller than 'minSum'.
     */
    int min_sum(vector<double> const &data, double const minSum)
    {
        int pos = -1;
        double sum = 0;
        for (size_t idx = 0; idx != data.size(); ++idx) 
        {
            sum += data[idx];
            if (sum >= minSum)
                pos = idx;
        }

        return pos;
    }

    /*
     * Return the approximate gain obtained by the value iteration.
     * This is given by max(vec1-vec2) + min(vec1, vec2) / 2
     */
    double approximate_gain(vector<double> const &vec1, vector<double> const &vec2)
    {
        // Obtain difference vector
        vector<double> diff_vec;
        transform(begin(vec1), end(vec1), begin(vec2), back_inserter(diff_vec), minus<double>());

        auto min_and_max = minmax_element(begin(diff_vec), end(diff_vec));

        return ((*min_and_max.second + *min_and_max.first)/2);
    }
}
