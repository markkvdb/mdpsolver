#include "mdp.ih"

#include <fstream>

/*
 * Write the optimal policy to output file in CSV format.
 * Optimal policy is defined by optimal maintenance and 
 * production in every state for every unit.
 */

void MDP::write_solution() const
{
    ofstream outputFile;
    outputFile.open("output/optimal_policy" + to_string(d_id) + ".csv");

    // Define header of the file (space separated)
    outputFile << "state1 state2 maintenance1 maintenance2 production1 production2" << endl;

    // Loop over all states
    size_t idxState = 0;
    for (size_t sdx1 = 0; sdx1 != d_nStates; ++sdx1)
    {
        for (size_t sdx2 = 0; sdx2 != d_nStates; ++sdx2)
        {
            outputFile << sdx1 << ' ' << sdx2 << ' ';
            outputFile << d_optimalMaintenance[idxState][0] << ' ' << d_optimalMaintenance[idxState][1] << ' ';
            outputFile << d_optimalProduction[idxState][0] << ' ' << d_optimalProduction[idxState][1] << endl;
            ++idxState;
        }
    }
    outputFile.close();
}