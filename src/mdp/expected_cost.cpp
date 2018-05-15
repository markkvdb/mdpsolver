#include "mdp.ih"

/*
    Calculate the expected cost for a given state 

    TODO obvious improvement is to restrict 'pdx2' to 'd_pi - pdx1'
    We assume that '2*d_nRates > d_pi > d_nRates'
*/

num_t MDP::expected_cost(size_t state1, size_t state2, size_t idxState)
{
    num_t bestVal = numeric_limits<num_t>::max();
    num_t bestProd1 = numeric_limits<num_t>::max();
    num_t bestProd2 = numeric_limits<num_t>::max();

    // Select minimum costs for all possible production states
    for (size_t pdx1 = (d_pi - d_nRates); pdx1 != d_nRates; ++pdx1)
    {
        size_t pdx2 = d_pi - pdx1 - 1;
        if (not feasible_production(state1, state2, pdx1, pdx2))
            continue;
        
        num_t const tmpVal(expected_costs(state1, state2, pdx1, pdx2));
        if (tmpVal < bestVal) {
            bestVal = tmpVal;
            bestProd1 = pdx1;
            bestProd2 = pdx2;
        }
    }

    d_optimalProduction[idxState][0] = bestProd1;
    d_optimalProduction[idxState][1] = bestProd2;
    
    return bestVal;
}