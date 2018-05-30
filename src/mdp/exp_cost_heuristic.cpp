#include "mdp.ih"

/*
    For every state we calculate the new value 
    to obtain V_t+1
*/

void MDP::exp_cost_heuristic1()
{
    int idxState = 0;

    for (int state1 = 0; state1 != d_nStates; ++state1)
    {
        for (int state2 = 0; state2 != d_nStates; ++state2) 
        {
            d_expectedCostHeuristic[idxState] = expected_cost_heuristic1(state1, state2, idxState);
            ++idxState;
        }
    }    
}

/*
    For every state we calculate the new value 
    to obtain V_t+1 (without production heuristic)
*/

void MDP::exp_cost_heuristic2()
{
    int idxState = 0;

    for (int state1 = 0; state1 != d_nStates; ++state1)
    {
        for (int state2 = 0; state2 != d_nStates; ++state2) 
        {
            d_expectedCostHeuristic[idxState] = expected_cost_heuristic2(state1, state2, idxState);
            ++idxState;
        }
    }    
}