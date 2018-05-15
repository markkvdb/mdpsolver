#include "mdp.ih"

MDP::MDP(Init const &init)
:
    d_valueA(vector<num_t>(init.d_nStates * init.d_nStates, 0)),
    d_valueB(vector<num_t>(init.d_nStates * init.d_nStates, 0)),
    d_expectedCost(vector<num_t>(init.d_nStates * init.d_nStates, 0)),
    d_optimalMaintenance(vector<array<size_t, 2>>(init.d_nStates * init.d_nStates, array<size_t, 2>())),
    d_optimalProduction(vector<array<size_t, 2>>(init.d_nStates * init.d_nStates, array<size_t, 2>())),
    d_ccm(init.d_ccm),
    d_cpm(init.d_cpm),
    d_C(init.d_C),
    d_nStates(init.d_nStates),
    d_pi(init.d_pi),
    d_nRates(init.d_nRates),
    d_minWorkingUnits(init.d_minWorkingUnits),
    d_prop1(init.d_prop1),
    d_prop2(init.d_prop2),
    d_eps(init.d_eps)
{
    if (d_pi < d_nRates || d_pi > (2 * d_nRates))
        throw string("Pi should be between nRates and 2*nRates");
}