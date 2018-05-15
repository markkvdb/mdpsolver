#include "bs.h"

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
     * TODO check if O(n) is fastest for obtaining differnence vector... I think so
     */ 
    double span(vector<double> const &first, vector<double> const &second)
    {  
        size_t length = first.size();
        
        if (length != second.size())
            throw string("Error: vectors do not have same length (bs::span(first, second))");

        vector<double> diff(length, 0);
        for (size_t idx = 0; idx != length; ++idx)
            diff[idx] = first[idx] - second[idx];
        
        auto result = minmax_element(diff.begin(), diff.end());

        return *result.second - *result.first;
    }

    /*
     * Return the first element such that the sum of all
     * elements till this element is at least 'value'.
     * 
     * Return size of 'data' vector if sum is smaller than 'minSum'.
     */
    size_t min_sum(std::vector<double> const &data, double const minSum)
    {
        size_t pos = data.size();
        double sum = 0;
        for (size_t idx = 0; idx != data.size(); ++idx) 
        {
            sum += data[idx];
            if (sum >= minSum)
                pos = idx;
        }

        return pos;
    }
}