#include "mdp.ih"

void MDP::value_cost()
{
    int idxState = 0;
    
    for (int state1 = 0; state1 != d_nStates; ++state1)
    {
        for (int state2 = 0; state2 != d_nStates; ++state2)
        {
            d_valueB[idxState] = value_costs(state1, state2, idxState);
            ++idxState;
        }
    }
}

// void MDP::value_cost()
// {
//     int idxState = 0;

//     for (int state1 = 0; state1 != d_nStates; ++state1)
//     {
//         for (int state2 = 0; state2 != d_nStates; ++state2)
//         {
//             for (int state3 = 0; state3 != d_nStates; ++state3)
//             {
//                 d_valueB[idxState] = value_costs(state1, state2, state3, idxState);
//                 ++idxState;
//             }
//         }
//     }
// }