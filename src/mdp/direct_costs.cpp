#include "mdp.ih"

/*
 * Return direct cost of unit in state 'state' and
 * selecting maintenance action 'mainAction'
 */

num_t MDP::direct_costs(size_t state, size_t mainAction)
{
    if (mainAction == 0)
        return 0;

    if (state == d_nRates)
        return d_ccm;
    else
        return d_cpm;
}