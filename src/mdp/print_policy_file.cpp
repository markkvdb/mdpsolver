#include "mdp.ih"

string MDP::print_policy_file(vector<array<int, 2>> const &maintenancePolicy,
                              vector<array<int, 2>> const &productionPolicy) const 
{
    ostringstream os;

    // Define header of the file (space separated)
    os << "state1 state2 maintenance1 maintenance2 production1 production2" << endl;

    // Loop over all states
    int idxState = 0;
    for (int sdx1 = 0; sdx1 != d_nStates; ++sdx1)
    {
        for (int sdx2 = 0; sdx2 != d_nStates; ++sdx2)
        {
            os << sdx1 << ' ' << sdx2 << ' ';
            os << maintenancePolicy[idxState][0] << ' ' << maintenancePolicy[idxState][1] << ' ';
            os << productionPolicy[idxState][0] << ' ' << productionPolicy[idxState][1] << endl;
            ++idxState;
        }
    }

    return os.str();
}