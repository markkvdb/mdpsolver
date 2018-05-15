#include "mdp.ih"

/*
 *  Calculate the expected cost for a given state and action.
 *  Loop over all possible jumps to states
 * 
 *  TODO check if I did the looping right
 */

num_t MDP::expected_costs(size_t state1, size_t state2, size_t prodRate1, size_t prodRate2)
{
    num_t costs = 0;
    size_t idxState = 0;

    // Loop over all jump probabilities from 'state1' to 'd_nStates' and obtain costs.
    size_t maxJump1 = d_nStates-state1-1;
    size_t maxJump2 = d_nStates-state2-1;

    for (size_t sdx1 = 0; sdx1 != maxJump1; ++sdx1) 
    {
        num_t prop1 = d_prop1[prodRate1][sdx1];
        for (size_t sdx2 = 0; sdx2 != maxJump2; ++sdx2)
        {
            costs += prop1 * d_prop1[prodRate2][sdx2] * d_valueA[idxState++];
        }
        costs += prop1 * d_prop2[prodRate2][state2] * d_valueA[idxState++];
    }

    // Add costs when unit 1 goes to failed state;
    num_t prop1 = d_prop2[prodRate1][state1];
    for (size_t sdx2 = 0; sdx2 != maxJump2; ++sdx2)
    {
        costs += prop1 * d_prop1[prodRate2][sdx2] * d_valueA[idxState++];
    }
    costs += prop1 * d_prop2[prodRate2][state2] * d_valueA[idxState++];

    return costs;
}