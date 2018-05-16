#include "mdp.ih"

num_t MDP::direct_cost(size_t state1, size_t state2, size_t mainAction1, size_t mainAction2) const
{
    // First check if there is any maintenance action
    size_t sumAction = mainAction1 + mainAction2;
    if (sumAction == 0)
        return 0;

    return d_C + direct_costs(state1, mainAction1) + direct_costs(state2, mainAction2);
}