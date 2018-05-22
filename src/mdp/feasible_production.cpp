#include "mdp.ih"

/*
 * If one of the machines is failed we cannot produce.
 */

bool MDP::feasible_production(size_t state1, size_t state2, size_t prodRate1, size_t prodRate2) const
{
    return not (((state1 == (d_nStates - 1)) and (prodRate1 > 0)) or ((state2 == (d_nStates - 1)) and (prodRate2 > 0)));
}