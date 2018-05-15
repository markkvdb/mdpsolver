#include "mdp.ih"

/*
 * For every state (s1, s2) we calculate the optimal 
 * maintenance policy. 
 * Action 0 is 'DN' and 1 is 'M'
 */

num_t MDP::value_costs(size_t state1, size_t state2)
{
    size_t s1, s2;
    num_t tmpVal = numeric_limits<num_t>::max();
    num_t bestVal = numeric_limits<num_t>::max();

    for (size_t adx1 = 0; adx1 != 2; ++adx1)
    {
        s1 = (adx1 == 0) ? state1 : 0;
        for (size_t adx2 = 0; adx2 != 2; ++adx2)
        {
            s2 = (adx2 == 0) ? state2 : 0;
            if (feasible_maintenance(state1, state2, adx1, adx2))
                tmpVal = direct_cost(state1, state2, adx1, adx2) + d_expectedCost[hash(s1, s2)];

            if (tmpVal < bestVal)
                bestVal = tmpVal;
        }
    }

    return bestVal;    
}