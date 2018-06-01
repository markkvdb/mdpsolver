#include "mdp.ih"

/*
 * Obtain optimal values for the heuristic and return the average cost.
 * Heuristic consists of two parts:
 *  1) Maintenaince heuristic
 *  2) Production heuristic
 */

num_t MDP::cost_heuristic(bool mHeuristic, bool pHeuristic)
{
    num_t minCosts = numeric_limits<num_t>::max();

    if (mHeuristic)
    {
        for (int T_r = d_nStates / 2; T_r != d_nStates; ++T_r)
        {
            for (int T_o = 0; T_o <= T_r; ++T_o)
            {
                // Evaluate policy
                solve_heuristic(mHeuristic, pHeuristic, T_r, T_o);
                num_t const tmpCosts = bs::approximate_gain(d_valueBHeuristic, d_valueAHeuristic);

                if (tmpCosts < minCosts)
                {
                    minCosts = tmpCosts;
                    d_optimalMaintenanceHeuristic = d_maintenanceHeuristic;
                }
            }
        }
    } else 
    {
        // Evaluate policy
        solve_heuristic(mHeuristic, pHeuristic, -1, -1);
        minCosts = bs::approximate_gain(d_valueBHeuristic, d_valueAHeuristic);   
    }

    return minCosts;
}