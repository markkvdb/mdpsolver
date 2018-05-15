#include "mdp.ih"

bool MDP::converged() const
{
    num_t const span = bs::span(d_valueB, d_valueA);
    
    return (span < d_eps);
}