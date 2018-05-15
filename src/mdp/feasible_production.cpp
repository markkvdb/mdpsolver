#include "mdp.ih"

/*
 * If one of the machines is failed we cannot produce.
 */

bool MDP::feasible_production(size_t state1, size_t state2, size_t prodRate1, size_t prodRate2)
{
    if (((state1 == (d_nStates - 1)) & (prodRate1 > 0)) || ((state2 == (d_nStates - 1)) & (prodRate2 > 0)))
        return false;
    
    return true;
}