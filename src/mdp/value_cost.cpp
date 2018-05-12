#include "mdp.ih"

void MDP::value_cost()
{
    for (size_t state1 = 0; state1 != d_nStates; ++state1)
        for (size_t state2 = 0; state2 != d_nStates; ++state2)
            d_valueB[hash(state1, state2)] = value_costs(state1, state2);
}