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
    outputFile << print_policy_file(d_optimalMaintenance, d_optimalProduction);
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

    // Heuristic information

    // Heuristic 1
    outputFile.open("output/heuristic1_policy" + to_string(d_id) + ".csv");
    num_t heuristicCost1 = cost_heuristic(true, false);
    outputFile << print_policy_file(d_optimalMaintenanceHeuristic, d_optimalProductionHeuristic);
    outputFile.close();

    // Heuristic 2
    outputFile.open("output/heuristic2_policy" + to_string(d_id) + ".csv");
    num_t heuristicCost2 = cost_heuristic(false, true);
    outputFile << print_policy_file(d_optimalMaintenanceHeuristic, d_optimalProductionHeuristic);
    outputFile.close();

    // Heuristic 3
    outputFile.open("output/heuristic3_policy" + to_string(d_id) + ".csv");
    num_t heuristicCost3 = cost_heuristic(true, true);
    outputFile << print_policy_file(d_optimalMaintenanceHeuristic, d_optimalProductionHeuristic);
    outputFile.close();


    outputFile.open("output/approximate_gain_heuristics" + to_string(d_id));
    outputFile << heuristicCost1 << ' ' << heuristicCost2 << ' ' << heuristicCost3 << endl;
    outputFile.close();
}