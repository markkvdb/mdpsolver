#include "mdp.ih"

size_t MDP::s_id = 0;

MDP::MDP(Init const &init, bool jumpHeuristic)
:
    d_id(s_id),
    d_valueA(vector<num_t>(init.d_nStates * init.d_nStates, 0)),
    d_valueB(vector<num_t>(init.d_nStates * init.d_nStates, 0)),
    d_expectedCost(vector<num_t>(init.d_nStates * init.d_nStates, 0)),
    d_optimalMaintenance(vector<array<int, 2>>(init.d_nStates * init.d_nStates, array<int, 2>())),
    d_optimalProduction(vector<array<int, 2>>(init.d_nStates * init.d_nStates, array<int, 2>())),
    d_ccm(init.d_ccm),
    d_cpm(init.d_cpm),
    d_C(init.d_C),
    d_nStates(init.d_nStates),
    d_pi(init.d_pi),
    d_nRates(init.d_nRates),
    d_minWorkingUnits(init.d_minWorkingUnits),
    d_prop1(init.d_prop1),
    d_prop2(init.d_prop2),
    d_jumpHeuristic(jumpHeuristic),
    d_maxJumps(init.d_maxJumps),
    d_terminalCosts(init.d_terminalCosts),
    d_eps(init.d_eps),
    d_optimalMaintenanceHeuristic(vector<array<int, 2>>(init.d_nStates * init.d_nStates, array<int, 2>())),
    d_optimalProductionHeuristic(vector<array<int, 2>>(init.d_nStates * init.d_nStates, array<int, 2>())),
    d_valueAHeuristic(vector<num_t>(init.d_nStates * init.d_nStates, 0)),
    d_valueBHeuristic(vector<num_t>(init.d_nStates * init.d_nStates, 0)),
    d_expectedCostHeuristic(vector<num_t>(init.d_nStates * init.d_nStates, 0))
{
    if (d_pi > 2 * (d_nRates-1))
        throw string("Error: pi should be feasible for units");

    ++s_id;
}


/*
 * For 3 units
 */

// MDP::MDP(Init const &init, bool jumpHeuristic)
// :
//     d_id(s_id),
//     d_valueA(vector<num_t>(init.d_nStates * init.d_nStates * init.d_nStates, 0)),
//     d_valueB(vector<num_t>(init.d_nStates * init.d_nStates * init.d_nStates, 0)),
//     d_expectedCost(vector<num_t>(init.d_nStates * init.d_nStates * init.d_nStates, 0)),
//     d_optimalMaintenance(vector<array<int, 3>>(init.d_nStates * init.d_nStates * init.d_nStates, array<int, 3>())),
//     d_optimalProduction(vector<array<int, 3>>(init.d_nStates * init.d_nStates * init.d_nStates, array<int, 3>())),
//     d_ccm(init.d_ccm),
//     d_cpm(init.d_cpm),
//     d_C(init.d_C),
//     d_nStates(init.d_nStates),
//     d_pi(init.d_pi),
//     d_nRates(init.d_nRates),
//     d_minWorkingUnits(init.d_minWorkingUnits),
//     d_prop1(init.d_prop1),
//     d_prop2(init.d_prop2),
//     d_jumpHeuristic(jumpHeuristic),
//     d_maxJumps(init.d_maxJumps),
//     d_terminalCosts(init.d_terminalCosts),
//     d_eps(init.d_eps)
// {
//     ++s_id;
// }