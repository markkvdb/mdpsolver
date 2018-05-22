#include "mdp.ih"

/*
    For every state we calculate the new value 
    to obtain V_t+1
*/

void MDP::exp_cost()
{
    size_t idxState = 0;
    
    for (size_t state1 = 0; state1 != d_nStates; ++state1)
        for (size_t state2 = 0; state2 != d_nStates; ++state2)
            d_expectedCost[idxState] = expected_cost(state1, state2, idxState++);
}