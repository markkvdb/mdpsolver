#include "mdp.ih"

void MDP::value_cost_heuristic1()
{
    int idxState = 0;
    
    for (int state1 = 0; state1 != d_nStates; ++state1)
    {
        for (int state2 = 0; state2 != d_nStates; ++state2)
        {
            d_valueBHeuristic[idxState] = value_costs_heuristic1(state1, state2, idxState);
            ++idxState;
        }
    }
}

void MDP::value_cost_heuristic2()
{
    int idxState = 0;
    
    for (int state1 = 0; state1 != d_nStates; ++state1)
    {
        for (int state2 = 0; state2 != d_nStates; ++state2)
        {
            d_valueBHeuristic[idxState] = value_costs_heuristic2(state1, state2, idxState);
            ++idxState;
        }
    }
}

void MDP::value_cost_heuristic3()
{
    int idxState = 0;
    
    for (int state1 = 0; state1 != d_nStates; ++state1)
    {
        for (int state2 = 0; state2 != d_nStates; ++state2)
        {
            d_valueBHeuristic[idxState] = value_costs_heuristic3(state1, state2, idxState);
            ++idxState;
        }
    }
}