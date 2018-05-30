#include "mdp.ih"

/*
 * Value costs for using heuristic for only maintenance 
 */
num_t MDP::value_costs_heuristic1(int state1, int state2, int idxState)
{
    int adx1 = d_optimalMaintenanceHeuristic[idxState][0];
    int adx2 = d_optimalMaintenanceHeuristic[idxState][1];
    int s1 = (adx1 == 0) ? state1 : 0;
    int s2 = (adx2 == 0) ? state2 : 0;

    return direct_cost(state1, state2, adx1, adx2) + d_expectedCost[hash(s1, s2)];
}

/*
 * Value costs for using heuristic for only production
 */
num_t MDP::value_costs_heuristic2(int state1, int state2, int idxState)
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

            num_t const tmpVal = direct_cost(state1, state2, adx1, adx2) + d_expectedCostHeuristic[hash(s1, s2)];
            if (tmpVal < bestVal - gg_eps)
            {
                bestVal = tmpVal;
                bestMain1 = adx1;
                bestMain2 = adx2;
            }
        }
    }

    d_optimalMaintenanceHeuristic[idxState][0] = bestMain1;
    d_optimalMaintenanceHeuristic[idxState][1] = bestMain2;
    
    return bestVal;  
}

/*
 * Value costs for using heuristic for both maintenance
 * and production
 */
num_t MDP::value_costs_heuristic3(int state1, int state2, int idxState)
{
    int adx1 = d_optimalMaintenanceHeuristic[idxState][0];
    int adx2 = d_optimalMaintenanceHeuristic[idxState][1];
    int s1 = (adx1 == 0) ? state1 : 0;
    int s2 = (adx2 == 0) ? state2 : 0;

    return direct_cost(state1, state2, adx1, adx2) + d_expectedCostHeuristic[hash(s1, s2)];
}