#include "mdp.ih"

/*
 *  Calculate the expected cost for a given state and action.
 *  Loop over all possible jumps to states
 * HEURISTIC
 */

num_t MDP::expected_costs_heuristic(int state1, int state2, int prodRate1, int prodRate2) const
{
    num_t costs = 0;

    // Check if we do all jumps or selection.
    int maxJump1 = d_nStates-state1-1;
    int maxJump2 = d_nStates-state2-1;

    if (d_jumpHeuristic) 
    {
        maxJump1 = min(maxJump1, d_maxJumps[prodRate1]);
        maxJump2 = min(maxJump2, d_maxJumps[prodRate2]);
    } 

    // Loop over all jump probabilities from 'state1' to 'd_nStates' and obtain costs.
    int idxState = hash(state1, 0);
    for (int sdx1 = 0; sdx1 != maxJump1; ++sdx1) 
    {
        num_t prop1 = d_prop1[prodRate1][sdx1];
        idxState += state2;

        for (int sdx2 = 0; sdx2 != maxJump2; ++sdx2)
            costs += prop1 * d_prop1[prodRate2][sdx2] * d_valueAHeuristic[idxState++];
        costs += prop1 * d_prop2[prodRate2][state2] * d_valueAHeuristic[idxState++];
    }

    // Add costs when unit 1 goes to failed state;
    num_t prop1 = d_prop2[prodRate1][state1];
    idxState += state2;

    for (int sdx2 = 0; sdx2 != maxJump2; ++sdx2)
    {
        costs += prop1 * d_prop1[prodRate2][sdx2] * d_valueAHeuristic[idxState++];
    }
    costs += prop1 * d_prop2[prodRate2][state2] * d_valueAHeuristic[idxState++];

    return costs;
}