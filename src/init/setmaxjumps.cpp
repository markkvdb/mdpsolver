#include "init.ih"

/*
 * Specify the maximum number of jumps for every production rate.
 */

void Init::setMaximumJump()
{
    d_maxJumps = vector<size_t>(d_nRates, 0);

    for (size_t adx = 0; adx != d_nRates; ++adx)
        d_maxJumps[adx] = bs::min_sum(d_prop1[adx], d_minSumJump);
}