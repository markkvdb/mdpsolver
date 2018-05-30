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
    // Initialise random generator
    random_device rd;
    mt19937 gen(rd());

    num_t totalCosts = 0;
    num_t detState1 = 0;
    num_t detState2 = 0;
    vector<vector<discrete_distribution<>>> jumpProbabilities = distribution_sampler();

    // Run simulation for simTime time units
    for (int t = 0; t != simTime; ++t)
    {
        // Check if we perform maintenance on unit 1
        if (maintenancePolicy[hash(detState1, detState2)][1])
        {
            detState1 = 0;
            if (detState1 == (d_nStates-1))
                totalCosts += d_ccm;
            else
                totalCosts += d_cpm;
        }

        // Check if we perform maintenance on unit 2
        if (maintenancePolicy[hash(detState1, detState2)][2])
        {
            detState2 = 0;
            if (detState2 == (d_nStates-1))
                totalCosts += d_ccm;
            else
                totalCosts += d_cpm;
        }

        // Check if we have to pay fixed costs, i.e. at least one
        // maintenance action.
        if (maintenancePolicy[hash(detState1, detState2)][1] or maintenancePolicy[hash(detState1, detState2)][2])
            totalCosts += d_C;

        // Determine deterioration
        int prodRate1 = productionPolicy[hash(detState1, detState2)][0];
        int prodRate2 = productionPolicy[hash(detState1, detState2)][0];
        detState1 += jumpProbabilities[prodRate1][detState1](gen);
        detState2 += jumpProbabilities[prodRate2][detState2](gen);
    }

    // Mean cost per time unit is total cost divided by length of time
    return (totalCosts / simTime);
}