#include "mdp.ih"

/*
 * Check whether maintenance action is feasible, that is, do we have 
 * enough working units under the maintenance policy
 */

bool MDP::feasible_maintenance(int state1, int state2, int mainAction1, int mainAction2) const
{
    // Set this to number of units
    int nWorkingUnits = 2;
    
    if ((state1 == (d_nStates - 1)) and mainAction1 == 0)
        --nWorkingUnits;
    if ((state2 == (d_nStates - 1)) and mainAction2 == 0)
        --nWorkingUnits;
    
    return (nWorkingUnits >= d_minWorkingUnits);
}

bool MDP::feasible_maintenance(int state1, int state2, int state3, 
                               int mainAction1, int mainAction2, int mainAction3) const
{
    // Set this to number of units
    int nWorkingUnits = 3;
    
    if ((state1 == (d_nStates - 1)) and mainAction1 == 0)
        --nWorkingUnits;
    if ((state2 == (d_nStates - 1)) and mainAction2 == 0)
        --nWorkingUnits;
    if ((state3 == (d_nStates - 1)) and mainAction3 == 0)
        --nWorkingUnits;
    
    return (nWorkingUnits >= d_minWorkingUnits);
}