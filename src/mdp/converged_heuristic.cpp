#include "mdp.ih"

bool MDP::converged_heuristic() const
{
    num_t const span = bs::span(d_valueBHeuristic, d_valueAHeuristic);
    
    return (span < d_eps);
}