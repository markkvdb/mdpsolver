#ifndef INCLUDED_SOLVE_EXPERIMENTS_
#define INCLUDED_SOLVE_EXPERIMENTS_

#include <iostream>
#include <fstream>

#include "init/init.h"
#include "mdp/mdp.h"

void solve_experiment(Init const &init)
{
    // Initialise MDP
    init.printAllInfo();
    MDP mdp{init, false};
    mdp.solve();
    mdp.print_all_info();
    mdp.write_solution();
    std::cout << "Solved experiment " << mdp.get_id() << std::endl;
}

void solve_from_file()
{
    // Read experiment file
    std::string line;
    std::ifstream experimentsFile("data/experiment_input");
    std::vector<Init> init_vec;

    // Initialise all experiments
    if (experimentsFile.is_open())
    {
        while (getline(experimentsFile, line))
        {
            Init init{line};
            init_vec.push_back(init);
        }
        experimentsFile.close();
    } else 
    {
        throw("Could not open file");
    }

    // Solve all experiments in different threads
    for (Init const &init: init_vec)
        solve_experiment(init);
}
#endif