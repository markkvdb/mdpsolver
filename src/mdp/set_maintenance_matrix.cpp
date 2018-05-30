#include "mdp.ih"

/*
 * Return matrix with opportunistic maintenance heuristic.
 */

void MDP::set_maintenance_matrix(int T_r, int T_o)
{
    for (int sdx1 = 0; sdx1 != d_nStates; ++sdx1)
    {
        for (int sdx2 = 0; sdx2 != d_nStates; ++sdx2)
        {
            if (sdx1 >= T_r)
            {
                d_optimalMaintenanceHeuristic[hash(sdx1, sdx2)][0] = 1;
                if (sdx2 >= T_o)
                    d_optimalMaintenanceHeuristic[hash(sdx1, sdx2)][1] = 1;
                else
                    d_optimalMaintenanceHeuristic[hash(sdx1, sdx2)][1] = 0;
            } else if (sdx1 >= T_o)
            {
                if (sdx2 >= T_r)
                {
                    d_optimalMaintenanceHeuristic[hash(sdx1, sdx2)][0] = 1;
                    d_optimalMaintenanceHeuristic[hash(sdx1, sdx2)][1] = 1;
                } else 
                {
                    d_optimalMaintenanceHeuristic[hash(sdx1, sdx2)][0] = 0;
                    d_optimalMaintenanceHeuristic[hash(sdx1, sdx2)][1] = 0;
                }
            } else 
            {
                d_optimalMaintenanceHeuristic[hash(sdx1, sdx2)][0] = 0;
                if (sdx2 >= T_r)
                    d_optimalMaintenanceHeuristic[hash(sdx1, sdx2)][1] = 1;
                else
                    d_optimalMaintenanceHeuristic[hash(sdx1, sdx2)][1] = 0;
            }
        }
    }
}