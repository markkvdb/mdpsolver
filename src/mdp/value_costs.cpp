#include "mdp.ih"

/*
 * For every state (s1, s2) we calculate the optimal maintenance policy. 
 * Action 0 is 'DN' and 1 is 'M'.
 */

num_t MDP::value_costs(int state1, int state2, int idxState)
{
    num_t bestVal = numeric_limits<num_t>::max();
    int bestMain1 = -1;
    int bestMain2 = -1;

    for (int adx1 = 0; adx1 != 2; ++adx1)
    {
        int s1 = (adx1 == 0) ? state1 : 0;
        for (int adx2 = 0; adx2 != 2; ++adx2)
        {
            if (not feasible_maintenance(state1, state2, adx1, adx2))
                continue;

            int s2 = (adx2 == 0) ? state2 : 0;

            num_t const tmpVal = direct_cost(state1, state2, adx1, adx2) + d_expectedCost[hash(s1, s2)];
            if (tmpVal < bestVal - gg_eps)
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

/*
 * Value cost for 3 units
 */

num_t MDP::value_costs(int state1, int state2, int state3, int idxState)
{
    num_t bestVal = numeric_limits<num_t>::max();
    int bestMain1 = 2;
    int bestMain2 = 2;
    int bestMain3 = 2;

    for (int adx1 = 0; adx1 != 2; ++adx1)
    {
        for (int adx2 = 0; adx2 != 2; ++adx2)
        {
            for (int adx3 = 0; adx3 != 2; ++adx3)
            {
                if (not feasible_maintenance(state1, state2, state3, adx1, adx2, adx3))
                    continue;

                int s1 = (adx1 == 0) ? state1 : 0;
                int s2 = (adx2 == 0) ? state2 : 0;
                int s3 = (adx3 == 0) ? state3 : 0;

                num_t const tmpVal = direct_cost(state1, state2, state3, adx1, adx2, adx3) + d_expectedCost[hash(s1, s2, s3)];
                if (tmpVal < bestVal - gg_eps)
                {
                    bestVal = tmpVal;
                    bestMain1 = adx1;
                    bestMain2 = adx2;
                    bestMain3 = adx3;
                }
            }

        }
    }

    d_optimalMaintenance[idxState][0] = bestMain1;
    d_optimalMaintenance[idxState][1] = bestMain2;
    d_optimalMaintenance[idxState][2] = bestMain3;
    
    return bestVal;  
}