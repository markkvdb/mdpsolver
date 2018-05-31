#include "mdp.ih"

/*
 * If one of the machines is failed we cannot produce.
 */

bool MDP::feasible_production(int state1, int state2, int prodRate1, int prodRate2) const
{
    if (prodRate1 + prodRate2 != d_pi)
        return false;
    
    return not (((state1 == (d_nStates - 1)) and (prodRate1 > 0)) or ((state2 == (d_nStates - 1)) and (prodRate2 > 0)));
}

/*
 * If state 3 is negative, i.e. state1 + state2 > pi, then
 * return false. Otherwise check if prodrate is not positive
 * when broken.
 */
bool MDP::feasible_production(int state1, int state2, int state3,
                              int prodRate1, int prodRate2, int prodRate3) const
{
    if (state3 < 0)
        return false;

    return not (((state1 == (d_nStates - 1)) and (prodRate1 > 0)) or ((state2 == (d_nStates - 1)) and (prodRate2 > 0)) or ((state3 == (d_nStates - 1)) and (prodRate3 > 0)));
}