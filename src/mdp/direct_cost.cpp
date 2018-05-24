#include "mdp.ih"

num_t MDP::direct_cost(int state1, int state2, int mainAction1, int mainAction2) const
{
    // First check if there is any maintenance action
    int sumAction = mainAction1 + mainAction2;
    if (sumAction == 0)
        return 0;

    return d_C + direct_costs(state1, mainAction1) + direct_costs(state2, mainAction2);
}

num_t MDP::direct_cost(int state1, int state2, int state3, 
                       int mainAction1, int mainAction2, int mainAction3) const
{
    // First check if there is any maintenance action
    int sumAction = mainAction1 + mainAction2 + mainAction3;
    if (sumAction == 0)
        return 0;

    return d_C + direct_costs(state1, mainAction1) + direct_costs(state2, mainAction2) + direct_costs(state3, mainAction3);
}