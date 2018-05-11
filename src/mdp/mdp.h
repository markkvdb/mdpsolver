#ifndef INCLUDED_MDP_
#define INCLUDED_MDP_

#include <vector>

#include "../init/init.h"

class MDP
{
    std::vector<num_t> d_valueA;
    std::vector<num_t> d_valueB;

    size_t  d_nStates;
    num_t   d_eps;

    public:
        MDP(Init const &init);

        void solve();

    private:
        bool    converged();
        void    exp_cost();
        num_t   expected_cost(size_t state1, size_t state2);
        num_t   expected_costs(size_t state1, size_t state2, num_t prodRate1, num_t prodRate2);

        size_t hash(size_t state1, size_t state2);
};

inline size_t MDP::hash(size_t state1, size_t state2) 
{
    return state1 * d_nStates + state2;
}

#endif