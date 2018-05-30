#include "mdp.ih"

/*
 *  Print policy in wide format
 */

void MDP::print_policy(vector<array<int, 2>> const &policy) const
{
    // Header
    cout << setw(6) << "State ";
    for (int sdx2 = 0; sdx2 != d_nStates; ++sdx2)
        cout << setw(6) << sdx2 << ' ';
    cout << endl;

    // Values
    for (int sdx1 = 0; sdx1 != d_nStates; ++sdx1)
    {
        cout << setw(6) << sdx1 << ' ';
        for (int sdx2 = 0; sdx2 != d_nStates; ++sdx2)
            cout << setw(6) << string("(") + to_string(policy[hash(sdx1, sdx2)][0]) + string(",") + to_string(policy[hash(sdx1, sdx2)][1]) + string(")") << ' ';
        cout << endl;
    }
}