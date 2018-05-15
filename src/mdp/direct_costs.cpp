#include "mdp.ih"

/*
 * Return direct cost of unit in state 'state' and
 * selecting maintenance action 'mainAction'
 */

num_t MDP::direct_costs(size_t state, size_t mainAction) const
{
    if (mainAction == 0)
        return 0;

    if (state == (d_nRates - 1))
        return d_ccm;
    
    return d_cpm;
}