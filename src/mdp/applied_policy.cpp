#include "mdp.ih"

/*
 * Evaluate cost of policy using a simulation of length
 * 'simTime'.
 * 
 * TODO do we let the deterioration state be continuous?
 * Or do we determine the thresholds of our maintenancePolicy?
 */

num_t MDP::applied_policy(std::vector<std::array<int, 2> > maintenancePolicy,
                          std::vector<std::array<int, 2> > productionPolicy,
                          int simTime) const
{
    double totalCosts = 0;
    double detState1 = 0;
    double detState2 = 0;

    // Run simulation for simTime time units
    for (int t = 0; t != simTime; ++t)
    {
        // Check if we perform maintenance

        // Set production rate

        // Determine deterioration (DISCRETE OR CONTINUOUS)

    }

    // Mean cost per time unit is total cost divided by length of time
    return (totalCosts / simTime);
}