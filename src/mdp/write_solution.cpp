#include "mdp.ih"

#include <fstream>

/*
 * Write the optimal policy to output file in CSV format.
 * Optimal policy is defined by optimal maintenance and 
 * production in every state for every unit.
 */

void MDP::write_solution()
{
    // Save the optimal policy
    ofstream outputFile;
    outputFile.open("output/optimal_policy" + to_string(d_id) + ".csv");

    // Define header of the file (space separated)
    outputFile << "state1 state2 maintenance1 maintenance2 production1 production2" << endl;

    // Loop over all states
    int idxState = 0;
    for (int sdx1 = 0; sdx1 != d_nStates; ++sdx1)
    {
        for (int sdx2 = 0; sdx2 != d_nStates; ++sdx2)
        {
            outputFile << sdx1 << ' ' << sdx2 << ' ';
            outputFile << d_optimalMaintenance[idxState][0] << ' ' << d_optimalMaintenance[idxState][1] << ' ';
            outputFile << d_optimalProduction[idxState][0] << ' ' << d_optimalProduction[idxState][1] << endl;
            ++idxState;
        }
    }
    outputFile.close();

    // Save optimal values
    outputFile.open("output/optimal_values" + to_string(d_id) + ".csv");
    for (num_t const val: d_valueB)
        outputFile << val << ' ';
    
    outputFile.close();

    // Save approximation gain
    outputFile.open("output/approximate_gain" + to_string(d_id));
    outputFile << bs::approximate_gain(d_valueB, d_valueA) << endl;
    outputFile.close();

    // Obtain heuristic value
    num_t heuristicCost = cost_heuristic(true, true);
    print_policy(d_optimalMaintenanceHeuristic);
    print_policy(d_optimalProductionHeuristic);
    cout << heuristicCost << endl;
}