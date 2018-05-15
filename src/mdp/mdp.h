#ifndef INCLUDED_MDP_
#define INCLUDED_MDP_

#include <vector>
#include <tuple>

#include "../init/init.h"

class MDP
{
    // Values
    std::vector<num_t> d_valueA;
    std::vector<num_t> d_valueB;

    // Expected costs for every production rate
    std::vector<num_t> d_expectedCost;

    // Maintenance costs
    num_t const d_ccm;
    num_t const d_cpm;
    num_t const d_C;

    // State and action space
    size_t const d_nStates;
    size_t const d_pi;
    size_t const d_nRates;
    size_t const d_minWorkingUnits;

    // Jump probabilities
    std::vector<std::vector<num_t>> const d_prop1;
    std::vector<std::vector<num_t>> const d_prop2;

    // Costs
    std::vector<num_t> const d_terminalCosts;

    // Value iteration parameter
    num_t const d_eps;

    public:
        MDP() = delete;
        MDP(Init const &init);

        void solve();
        void print_all_info();

    private:
        void    value_cost();
        num_t   value_costs(size_t state1, size_t state2);
        bool    feasible_maintenance(size_t state1, size_t state2, size_t mainAction1, size_t mainAction2);
        bool    feasible_production(size_t state1, size_t state2, size_t prodRate1, size_t prodRate2);
        num_t   direct_cost(size_t state1, size_t state2, size_t mainAction1, size_t mainAction2);
        num_t   direct_costs(size_t state, size_t mainAction);
        bool    converged() const;
        void    exp_cost();
        num_t   expected_cost(size_t state1, size_t state2);
        num_t   expected_costs(size_t state1, size_t state2, size_t prodRate1, size_t prodRate2);

        size_t                      hash(size_t state1, size_t state2) const;
        std::tuple<size_t, size_t>  inv_hash(size_t states) const;
};

inline size_t MDP::hash(size_t state1, size_t state2) const
{
    return state1 * d_nStates + state2;
}

inline std::tuple<size_t, size_t> MDP::inv_hash(size_t states) const
{
    size_t leftOver = states % d_nStates;
    return std::make_tuple((states - leftOver) / d_nStates, leftOver);
}

#endif