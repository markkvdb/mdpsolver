#include "mdp.ih"

/*
 * Create row for optimal cost table.
 */

void MDP::print_latex_table(num_t optimalCost, num_t heuristicCost1, num_t heuristicCost2,
                            num_t heuristicCost3) const
{
    ofstream outputFile;

    // If it is first experiment, clear file, otherwise append file.
    if (d_id == 0)
        outputFile.open("output/cost_table.tex");
    else
        outputFile.open("output/cost_table.tex", ofstream::app);

    outputFile << heuristicCost1 << " (" << ((heuristicCost1 - optimalCost) / optimalCost) * 100 << "%)" << "&";
    outputFile << heuristicCost2 << " (" << ((heuristicCost2 - optimalCost) / optimalCost) * 100 << "%)" << "&";
    outputFile << heuristicCost3 << " (" << ((heuristicCost3 - optimalCost) / optimalCost) * 100 << "%)" << "//" << endl;
    outputFile.close();
}