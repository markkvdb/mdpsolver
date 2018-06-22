#ifndef INCLUDED_SOLVE_EXPERIMENTS_
#define INCLUDED_SOLVE_EXPERIMENTS_

#include <iostream>
#include <fstream>

#include <thread>

#include "init/init.h"
#include "mdp/mdp.h"

void solve_experiment(Init const init)
{
    // Initialise MDP
    MDP mdp{init, false};
    mdp.solve();
    mdp.write_solution();
}

void solve_from_file(bool const multi_thread)
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
    if (multi_thread)
    {
        std::vector<std::thread> thread_vec;
        for (Init const &init: init_vec)
            thread_vec.push_back(std::thread(solve_experiment, init));
        
        // Wait for all threads to join
        for (auto &thread: thread_vec)
            thread.join();

    } else 
    {
        for (Init const &init: init_vec)
            solve_experiment(init);
    }
}
#endif