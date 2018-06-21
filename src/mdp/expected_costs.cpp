#include "mdp.ih"

/*
 *  Calculate the expected cost for a given state and action.
 *  Loop over all possible jumps to states
 * 
 *  TODO check if I did the looping right. idxState should be possible.
 *  TODO check if maxJumps should be 2d vector for every state.
 */

num_t MDP::expected_costs(int state1, int state2, int prodRate1, int prodRate2) const
{
    num_t costs = 0;

    // Check if we do all jumps or selection.
    int maxJump1 = d_nStates-state1-1;
    int maxJump2 = d_nStates-state2-1;

    // if (d_jumpHeuristic) 
    // {
    //     maxJump1 = min(maxJump1, d_maxJumps[prodRate1]);
    //     maxJump2 = min(maxJump2, d_maxJumps[prodRate2]);
    // } 

    // Loop over all jump probabilities from 'state1' to 'd_nStates' and obtain costs.
    int idxState = hash(state1, 0);
    for (int sdx1 = 0; sdx1 != maxJump1; ++sdx1) 
    {
        num_t prop1 = d_prop1[prodRate1][sdx1];
        idxState += state2;

        for (int sdx2 = 0; sdx2 != maxJump2; ++sdx2)
            costs += prop1 * d_prop1[prodRate2][sdx2] * d_valueA[idxState++];
        costs += prop1 * d_prop2[prodRate2][state2] * d_valueA[idxState++];
    }

    // Add costs when unit 1 goes to failed state;
    num_t prop1 = d_prop2[prodRate1][state1];
    idxState += state2;

    for (int sdx2 = 0; sdx2 != maxJump2; ++sdx2)
        costs += prop1 * d_prop1[prodRate2][sdx2] * d_valueA[idxState++];
    costs += prop1 * d_prop2[prodRate2][state2] * d_valueA[idxState++];

    return costs;
}

/*
 *  Expected costs for system of 3 units.
 */

num_t MDP::expected_costs(int state1, int state2, int state3, 
                          int prodRate1, int prodRate2, int prodRate3) const
{
    num_t costs = 0;

    // Check if we do all jumps or selection.
    int maxJump1 = d_nStates-state1-1;
    int maxJump2 = d_nStates-state2-1;
    int maxJump3 = d_nStates-state3-1;

    if (d_jumpHeuristic) 
    {
        maxJump1 = min(maxJump1, d_maxJumps[prodRate1]);
        maxJump2 = min(maxJump2, d_maxJumps[prodRate2]);
        maxJump3 = min(maxJump3, d_maxJumps[prodRate3]);
    } 

    // Unit 1 good
    int idxState = hash(state1, 0, 0);
    for (int sdx1 = 0; sdx1 != maxJump1; ++sdx1) 
    {
        num_t prop1 = d_prop1[prodRate1][sdx1];
        idxState += state2 * d_nRates;

        // Unit 1, 2 good
        for (int sdx2 = 0; sdx2 != maxJump2; ++sdx2)
        {
            num_t prop2 = prop1 * d_prop1[prodRate2][sdx2];
            idxState += state3;

            // Unit 1, 2, 3 good
            for (int sdx3 = 0; sdx3 != maxJump3; ++sdx3)
                costs += prop2 * d_prop1[prodRate3][sdx3] * d_valueA[idxState++];
            // Unit 1, 2 good; 3 bad
            costs += prop2 * d_prop2[prodRate3][state3] * d_valueA[idxState++];
        }

        // Unit 1 good; 2 bad
        num_t prop2 = prop1 * d_prop2[prodRate2][state2];
        idxState += state3;

        // Unit 1, 3 good; 2 bad
        for (int sdx3 = 0; sdx3 != maxJump3; ++sdx3)
            costs += prop2 * d_prop1[prodRate3][sdx3] * d_valueA[idxState++];
        // Unit 1 good; 2, 3 bad
        costs += prop2 * d_prop2[prodRate3][state3] * d_valueA[idxState++];
    }

    // Unit 1 bad
    num_t prop1 = d_prop2[prodRate1][state1];
    idxState += state2 * d_nRates;

    // Unit 2 good; 1 bad
    for (int sdx2 = 0; sdx2 != maxJump2; ++sdx2)
    {
        num_t prop2 = prop1 * d_prop1[prodRate2][sdx2];
        idxState += state3;

        // Unit 2, 3 good; 1 bad
        for (int sdx3 = 0; sdx3 != maxJump3; ++sdx3)
            costs += prop2 * d_prop1[prodRate3][sdx3] * d_valueA[idxState++];
        // Unit 2 good; 1, 3 bad
        costs += prop2 * d_prop2[prodRate3][state3] * d_valueA[idxState++];
    }

    // Unit 1, 2 bad
    num_t prop2 = prop1 * d_prop2[prodRate2][state2];
    idxState += state3;

    // Unit 3 good; 1, 2 bad
    for (int sdx3 = 0; sdx3 != maxJump3; ++sdx3)
        costs += prop2 * d_prop1[prodRate3][sdx3] * d_valueA[idxState++];
    // Unit 1, 2, 3 bad
    costs += prop2 * d_prop2[prodRate3][state3] * d_valueA[idxState++];

    return costs;
}