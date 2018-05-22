#include "mdp.ih"

/*
 * For every state (s1, s2) we calculate the optimal maintenance policy. 
 * Action 0 is 'DN' and 1 is 'M'.
 */

num_t MDP::value_costs(size_t state1, size_t state2, size_t idxState)
{
    num_t bestVal = numeric_limits<num_t>::max();
    size_t bestMain1 = 2;
    size_t bestMain2 = 2;

    for (size_t adx1 = 0; adx1 != 2; ++adx1)
    {
        size_t s1 = (adx1 == 0) ? state1 : 0;
        for (size_t adx2 = 0; adx2 != 2; ++adx2)
        {
            if (not feasible_maintenance(state1, state2, adx1, adx2))
                continue;

            size_t s2 = (adx2 == 0) ? state2 : 0;

            num_t const tmpVal = direct_cost(state1, state2, adx1, adx2) + d_expectedCost[hash(s1, s2)];
            if (tmpVal < bestVal)
            {
                bestVal = tmpVal;
                bestMain1 = adx1;
                bestMain2 = adx2;
            }
        }
    }

    d_optimalMaintenance[idxState][0] = bestMain1;
    d_optimalMaintenance[idxState][1] = bestMain2;
    
    return bestVal;    
}