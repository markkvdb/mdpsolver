#include "mdp.ih"

/*
 * Create a discrete distribution for every production rate in
 * every deterioration state.
 */

vector<vector<discrete_distribution<>>> MDP::distribution_sampler() const
{
    vector<vector<discrete_distribution<>>> jumpProbabilities;
    jumpProbabilities.resize(d_nRates);

    for (int sdx = 0; sdx != d_nStates; ++sdx)
    {
        for (int pdx = 0; pdx != d_nRates; ++pdx)
        {
            jumpProbabilities[pdx].resize(d_nStates);

            // Maximum number of jumps to non-failed states
            int maxJumps = (d_nStates-1) - sdx;
            vector<double> jumpProbability(maxJumps+1, 0);
            
            // Add all jumps to non-failed states
            for (int jump = 0; jump != maxJumps; ++jump)
                jumpProbability[jump] = d_prop1[pdx][jump];
            // Jump to failed state
            jumpProbability[maxJumps] = d_prop2[pdx][sdx];

            jumpProbabilities[pdx][sdx] = discrete_distribution<>(begin(jumpProbability), end(jumpProbability));
        }
    }

    return jumpProbabilities;
}