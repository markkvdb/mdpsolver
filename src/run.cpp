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
        solve_from_file();
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
                  0.9999,   // minProb
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
    cout << e << endl;
}