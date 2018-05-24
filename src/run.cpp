#include <iostream>
#include <fstream>

#include "init/init.h"
#include "mdp/mdp.h"

using namespace std;

int main(int argc, char**argv) 
try 
{
    if (argc == 2)
    {
        // Read experiment file
        string line;
        ifstream experimentsFile("data/experiment_input");
        size_t iter = 0;

        // Loop over all experiments
        if (experimentsFile.is_open())
        {
            while (getline(experimentsFile, line))
            {
                cout << "Solve experiment " << iter << endl;
                Init init{line};
                init.printAllInfo();
                MDP mdp{init};
                mdp.solve();
                mdp.write_solution();
                ++iter;
            }
            experimentsFile.close();
        } else 
        {
            throw("Could not open file");
        }
    } else
    {
        Init init{1,        // ccm
                  0.2,      // cpm
                  0.5,      // C
                  50,       // nStates
                  1,        // dL
                  60,       // pi
                  50,       // nRates
                  1,        // mu
                  2,        // var
                  1,        // dT
                  0.1,      // beta
                  1.5,      // alpha
                  0.000005, // eps
                  0.99,     // minProb
                  2         // nUnits
                 };


        // Initialise, solve and write mdp
        MDP mdp{init};
        mdp.solve();
        mdp.write_solution();
    }
}
catch (string const &e) 
{
    cout << e << '\n';
}