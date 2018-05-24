#ifndef INCLUDED_MDP_
#define INCLUDED_MDP_

#include <vector>
#include <array>
#include <tuple>

#include "../init/init.h"

class MDP
{
    static size_t   s_id;
    size_t const    d_id;
    
    // Values
    std::vector<num_t> d_valueA;
    std::vector<num_t> d_valueB;

    // Expected costs for every production rate
    std::vector<num_t> d_expectedCost;

    // Save optimal actions
    std::vector<std::array<size_t, 2>> d_optimalMaintenance;
    std::vector<std::array<size_t, 2>> d_optimalProduction;

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
        void solve2();
        void write_solution() const;
        void print_all_info() const;
        
        size_t get_id() const;

    private:
        void    value_cost();
        num_t   value_costs(size_t state1, size_t state2, size_t idxState);
        bool    feasible_maintenance(size_t state1, size_t state2, size_t mainAction1, size_t mainAction2) const;
        bool    feasible_production(size_t state1, size_t state2, size_t prodRate1, size_t prodRate2) const;
        num_t   direct_cost(size_t state1, size_t state2, size_t mainAction1, size_t mainAction2) const;
        num_t   direct_costs(size_t state, size_t mainAction) const;
        bool    converged() const;
        void    exp_cost();
        num_t   expected_cost(size_t state1, size_t state2, size_t idxState);
        num_t   expected_costs(size_t state1, size_t state2, size_t prodRate1, size_t prodRate2) const;

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

inline size_t MDP::get_id() const
{
    return d_id;
}

#endif