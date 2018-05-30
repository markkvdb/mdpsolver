#include "mdp.ih"

/*
 * Expected cost using production heuristic
 */

num_t MDP::expected_cost_heuristic1(int state1, int state2, int idxState)
{
    num_t bestVal = numeric_limits<num_t>::max();
    int bestProd1 = -1;
    int bestProd2 = -1;

    // Check if we should do one working unit
    if (d_pi <= d_nRates)
    {
        bestVal = expected_costs_heuristic(state1, state2, d_pi, 0);
        bestProd1 = d_pi;
        bestProd2 = 0;

        num_t const tmpVal2 = expected_costs_heuristic(state1, state2, 0, d_pi);

        if (tmpVal2 < bestVal)
        {
            bestVal = tmpVal2;
            bestProd1 = 0;
            bestProd2 = d_pi;
        }
    }

    // Share load
    int pdx1 = d_pi / 2;
    int pdx2 = d_pi - pdx1;
    num_t tmpVal3 = expected_costs_heuristic(state1, state2, pdx1, pdx2);

    if (tmpVal3 < bestVal)
    {
        bestVal = tmpVal3;
        bestProd1 = pdx1;
        bestProd2 = pdx2;
    }

    d_optimalProductionHeuristic[idxState][0] = bestProd1;
    d_optimalProductionHeuristic[idxState][1] = bestProd2;
    
    return bestVal;
}

/*
 * Expected cost using production heuristic
 */

num_t MDP::expected_cost_heuristic2(int state1, int state2, int idxState)
{
    num_t bestVal = numeric_limits<num_t>::max();
    int bestProd1 = -1;
    int bestProd2 = -1;

    // Select minimum costs for all possible production states
    for (int pdx1 = (d_pi - d_nRates + 1); pdx1 != d_nRates; ++pdx1)
    {
        int pdx2 = d_pi - pdx1;
        if (not feasible_production(state1, state2, pdx1, pdx2))
            continue;

        num_t const tmpVal = expected_costs_heuristic(state1, state2, pdx1, pdx2);

        if (tmpVal < bestVal - gg_eps) 
        {
            bestVal = tmpVal;
            bestProd1 = pdx1;
            bestProd2 = pdx2;
        }
    }

    d_optimalProductionHeuristic[idxState][0] = bestProd1;
    d_optimalProductionHeuristic[idxState][1] = bestProd2;
    
    return bestVal;
}