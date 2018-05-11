#include "init.ih"

/* 
 * This function set the terminal cost vector
 * i.e., the costs for being in a specific state at the end of the time horizon
 * The datamember d_terminalCosts is given to the MDP class
 */

void Init::setCost()
{
    d_terminalCosts = vector<num_t>(d_nStates, d_cpm);
    d_terminalCosts.back() = d_ccm;
}