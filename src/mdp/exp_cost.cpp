#include "mdp.ih"

/*
    For every state we calculate the new value 
    to obtain V_t+1
*/

void MDP::exp_cost()
{
    int idxState = 0;

    for (int state1 = 0; state1 != d_nStates; ++state1)
    {
        for (int state2 = 0; state2 != d_nStates; ++state2) 
        {
            d_expectedCost[idxState] = expected_cost(state1, state2, idxState);
            ++idxState;
        }
    }    
}

/*
 *  For 3 units
 */

// void MDP::exp_cost()
// {
//     int idxState = 0;

//     for (int state1 = 0; state1 != d_nStates; ++state1)
//     {
//         for (int state2 = 0; state2 != d_nStates; ++state2) 
//         {
//             for (int state3 = 0; state3 != d_nStates; ++state3)
//             {
//                 d_expectedCost[idxState] = expected_cost(state1, state2, state3, idxState);
//                 ++idxState;
//             }
//         }
//     }    
// }