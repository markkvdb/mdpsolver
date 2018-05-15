#include "mdp.ih"

/*
 * Check whether maintenance action is feasible, that is, do we have 
 * enough working units under the maintenance policy
 */

bool MDP::feasible_maintenance(size_t state1, size_t state2, size_t mainAction1, size_t mainAction2) const
{
    // Set this to number of units
    size_t nWorkingUnits = 2;
    
    if ((state1 == (d_nStates - 1)) && mainAction1 == 0)
        --nWorkingUnits;
    if ((state2 == (d_nStates - 1)) && mainAction2 == 0)
        --nWorkingUnits;
    
    return (nWorkingUnits >= d_minWorkingUnits);
}