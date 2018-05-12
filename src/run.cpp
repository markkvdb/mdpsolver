#include <iostream>

#include "init/init.h"
#include "mdp/mdp.h"

int main(int argc, char**argv) 
{
    Init init{1, 0.3, 10, 10, 0.1, 6, 5, 1, 2, 0.1, 0.0, 1, 0.0005};
    init.initialise();
    init.printTransitionMatrix();

    MDP mdp{init};
    mdp.solve();
    std::cout << "Hello world!\n";
}