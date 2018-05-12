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
    num_t prop1;

    // Loop over all jump probabilities from 'state1' to 'd_nStates' and obtain costs.
    for (size_t sdx1 = 0; sdx1 != (d_nStates-state1-1); ++sdx1) 
    {
        prop1 = d_prop1[prodRate1][sdx1];
        for (size_t sdx2 = 0; sdx2 != (d_nStates-state2-1); ++sdx2)
        {
            costs += prop1 * d_prop1[prodRate2][sdx2] * d_valueA[hash(sdx1, sdx2)];
        }
        costs += prop1 * d_prop2[prodRate2][state2] * d_valueA[hash(sdx1, d_nStates-1)];
    }

    // Add costs when unit 1 goes to failed state;
    prop1 = d_prop2[prodRate1][state1];
    for (size_t sdx2 = 0; sdx2 != (d_nStates-state2-1); ++sdx2)
    {
        costs += prop1 * d_prop1[prodRate2][sdx2] * d_valueA[hash(d_nStates-1, sdx2)];
    }
    costs += prop1 * d_prop2[prodRate2][state2] * d_valueA[hash(d_nStates, d_nStates-1)];

    return costs;
}