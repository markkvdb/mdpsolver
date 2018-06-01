#ifndef INCLUDED_MDP_
#define INCLUDED_MDP_

#include <vector>
#include <array>
#include <tuple>
#include <random>

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
    std::vector<std::array<int, 2> > d_optimalMaintenance;
    std::vector<std::array<int, 2> > d_optimalProduction;
    // std::vector<std::array<int, 3>> d_optimalMaintenance;
    // std::vector<std::array<int, 3>> d_optimalProduction;

    // Maintenance costs
    num_t const d_ccm;
    num_t const d_cpm;
    num_t const d_C;

    // State and action space
    int const d_nStates;
    int const d_pi;
    int const d_nRates;
    int const d_minWorkingUnits;

    // Jump probabilities
    std::vector<std::vector<num_t>> const d_prop1;
    std::vector<std::vector<num_t>> const d_prop2;

    // Jump heuristic
    bool                     d_jumpHeuristic;         
    std::vector<int> const   d_maxJumps;

    // Costs
    std::vector<num_t> const d_terminalCosts;

    // Value iteration parameter
    num_t const d_eps;

    // Heuristic
    std::vector<std::array<int, 2> > d_optimalMaintenanceHeuristic;
    std::vector<std::array<int, 2> > d_optimalProductionHeuristic;
    std::vector<std::array<int, 2> > d_maintenanceHeuristic;

    std::vector<num_t> d_valueAHeuristic;
    std::vector<num_t> d_valueBHeuristic;

    std::vector<num_t> d_expectedCostHeuristic;


    public:
        MDP() = delete;
        MDP(Init const &init, bool jumpHeuristic = false);

        void        solve();
        void        write_solution();
        void        print_all_info() const;
        void        print_policy(std::vector<std::array<int, 2>> const &policy) const;
        std::string print_policy_file(std::vector<std::array<int, 2>> const &maintenancePolicy,
                                      std::vector<std::array<int, 2>> const &productionPolicy) const;
        
        size_t get_id() const;

    private:
        // Generic functions
        void    value_cost();
        void    exp_cost();
        bool    converged() const;
        num_t   direct_costs(int state, int mainAction) const;

        // Heuristic functions
        num_t   cost_heuristic(bool mHeuristic, bool pHeuristic);
        num_t   applied_policy(std::vector<std::array<int, 2> > maintenancePolicy,
                               std::vector<std::array<int, 2> > productionPolicy,
                               int simTime) const;
        void    set_maintenance_matrix(int T_r, int T_o);
        num_t   expected_costs_heuristic(int state1, int state2, int prodRate1, int prodRate2) const;
        num_t   expected_cost_heuristic1(int state1, int state2, int idxState);
        num_t   expected_cost_heuristic2(int state1, int state2, int idxState);
        void    exp_cost_heuristic1();
        void    exp_cost_heuristic2();
        num_t   value_costs_heuristic1(int state1, int state2, int idxState);
        num_t   value_costs_heuristic2(int state1, int state2, int idxState);
        num_t   value_costs_heuristic3(int state1, int state2, int idxState);
        void    value_cost_heuristic1();
        void    value_cost_heuristic2();
        void    value_cost_heuristic3();
        void    solve_heuristic(bool mHeuristic, bool pHeuristic, int T_r, int T_o);
        bool    converged_heuristic() const;

        std::vector<std::vector<std::discrete_distribution<>>> distribution_sampler() const;

        // Functions for 2 unit system
        num_t   value_costs(int state1, int state2, int idxState);
        num_t   direct_cost(int state1, int state2, int mainAction1, int mainAction2) const;
        num_t   expected_cost(int state1, int state2, int idxState);
        num_t   expected_costs(int state1, int state2, int prodRate1, int prodRate2) const;
        bool    feasible_maintenance(int state1, int state2, int mainAction1, int mainAction2) const;
        bool    feasible_production(int state1, int state2, int prodRate1, int prodRate2) const;
        int     hash(int state1, int state2) const;

        // Functions for 3 unit system
        num_t   value_costs(int state1, int state2, int state3, int idxState);
        num_t   direct_cost(int state1, int state2, int state3, int mainAction1, 
                            int mainAction2, int mainAction3) const;
        num_t   expected_cost(int state1, int state2, int state3, int idxState);
        num_t   expected_costs(int state1, int state2, int state3, 
                               int prodRate1, int prodRate2, int prodRate3) const;
        bool    feasible_maintenance(int state1, int state2, int state3,
                                     int mainAction1, int mainAction2, int mainAction3) const;
        bool    feasible_production(int state1, int state2, int state3,
                                    int prodRate1, int prodRate2, int prodRate3) const;
        int     hash(int state1, int state2, int state3) const;

};

inline int MDP::hash(int state1, int state2) const
{
    return state1 * d_nStates + state2;
}

inline int MDP::hash(int state1, int state2, int state3) const
{
    return state1 * d_nStates * d_nStates + state2 * d_nStates + state3;
}

inline size_t MDP::get_id() const
{
    return d_id;
}

#endif