#include "mdp.ih"

void MDP::value_cost()
{
    size_t idxState = 0;
    
    for (size_t state1 = 0; state1 != d_nStates; ++state1) 
        for (size_t state2 = 0; state2 != d_nStates; ++state2) 
            d_valueB[idxState] = value_costs(state1, state2, idxState++);
}