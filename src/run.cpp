#include <iostream>
#include <fstream>

#include "init/init.h"
#include "mdp/mdp.h"

#include "solve_experiments.h"

using namespace std;


int main(int argc, char**argv) 
try 
{
    if (argc == 2)
    {
        solve_from_file(true);
    } else
    {
        Init init{11.0,        // ccm
                  5.0,      // cpm
                  4.0,      // C
                  21,       // nStates
                  1,        // dL
                  20,       // pi
                  21,       // nRates
                  1,        // mu
                  5,        // var
                  1,        // dT
                  0.1,      // beta
                  1.5,      // alpha
                  0.0000005, // eps
                  0.99,     // minProb
                  2         // nUnits
                 };

        // Initialise, solve and write mdp
        init.printAllInfo();
        MDP mdp{init, false};
        mdp.solve();
        mdp.write_solution();
    }
}
catch (string const &e) 
{
    cout << e << endl;
}