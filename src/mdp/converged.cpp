#include "mdp.ih"

bool MDP::converged()
{
    num_t span = bs::span(d_valueB, d_valueA);

    if (span < d_eps)
        return true;
    
    return false;
}