#include "mdp.ih"

/*
    For every state we calculate the new value 
    to obtain V_t+1
*/

void MDP::exp_cost()
{
    for (size_t x1 = 0; x1 != d_nStates; ++x1)
        for (size_t x2 = 0; x2 != d_nStates; ++x2)
            d_valueB[hash(x1, x2)] = expected_cost(x1, x2);
}