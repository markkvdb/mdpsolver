#include "mdp.ih"

void MDP::solve_heuristic(bool mHeuristic, bool pHeuristic, int T_r, int T_o)
{
    // If maintenance heuristic determine maintenance policy
    if (mHeuristic)
        set_maintenance_matrix(T_r, T_o);

    d_valueBHeuristic = vector<num_t>(d_nStates * d_nStates, 0);

    // Use all jump probabilities
    do
    {
        // Set new values to old values
        d_valueAHeuristic = d_valueBHeuristic;

        // Compute the expected cost for every state and optimal production
        if (pHeuristic)
            exp_cost_heuristic1();
        else
            exp_cost_heuristic2();

        // Obtain new value
        if (pHeuristic and mHeuristic)
        {  
            value_cost_heuristic3();
        } else if (mHeuristic)
        {
            value_cost_heuristic1();
        }
        else if (pHeuristic) 
        {
            value_cost_heuristic2();
        } else
        {
            throw(string("Specify heuristic"));
        }

    } while(not converged_heuristic());
}