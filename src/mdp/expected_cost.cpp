#include "mdp.ih"

/*
    Calculate the expected cost for a given state 

    TODO obvious improvement is to restrict 'pdx2' to 'd_pi - pdx1'
    We assume that '2*d_nRates > d_pi > d_nRates'
*/

num_t MDP::expected_cost(int state1, int state2, int idxState)
{
    num_t bestVal = numeric_limits<num_t>::max();
    int bestProd1 = -1;
    int bestProd2 = -1;

    // Select minimum costs for all possible production states
    for (int pdx1 = (d_pi - d_nRates + 1); pdx1 != d_nRates; ++pdx1)
    {
        int pdx2 = 0;
        if (pdx1 < d_pi)
            pdx2 = d_pi - pdx1;

        if (not feasible_production(state1, state2, pdx1, pdx2))
            continue;

        num_t const tmpVal = expected_costs(state1, state2, pdx1, pdx2);

        if (tmpVal < bestVal - gg_eps) 
        {
            bestVal = tmpVal;
            bestProd1 = pdx1;
            bestProd2 = pdx2;
        }
    }

    d_optimalProduction[idxState][0] = bestProd1;
    d_optimalProduction[idxState][1] = bestProd2;
    
    return bestVal;
}

num_t MDP::expected_cost(int state1, int state2, int state3, int idxState)
{
    num_t bestVal = numeric_limits<num_t>::max();
    int bestProd1 = d_nRates;
    int bestProd2 = d_nRates;
    int bestProd3 = d_nRates;

    // Select minimum costs for all possible production states
    for (int pdx1 = 0; pdx1 != d_nRates; ++pdx1)
    {
        for (int pdx2 = 0; pdx2 != d_nRates; ++pdx2)
        {
            int pdx3 = d_pi - pdx1 - pdx2;
            if (not feasible_production(state1, state2, state3, pdx1, pdx2, pdx3))
                continue;

            num_t const tmpVal = expected_costs(state1, state2, state3, pdx1, pdx2, pdx3);

            if (tmpVal < bestVal - gg_eps) 
            {
                bestVal = tmpVal;
                bestProd1 = pdx1;
                bestProd2 = pdx2;
                bestProd3 = pdx3;
            }
        }
    }

    d_optimalProduction[idxState][0] = bestProd1;
    d_optimalProduction[idxState][1] = bestProd2;
    d_optimalProduction[idxState][2] = bestProd3;
    
    return bestVal;
}