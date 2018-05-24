#include <iostream>

#include "init/init.h"
#include "mdp/mdp.h"

using namespace std;

int main(int argc, char**argv) 
try 
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
              0.99      // minProb
             };
    MDP mdp{init};
    mdp.solve();
    mdp.write_solution();
}
catch (string const &e) 
{
    cout << e << '\n';
}