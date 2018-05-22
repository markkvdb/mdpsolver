#include "mdp.ih"

void MDP::print_all_info()
{
    cout << setprecision(5) << fixed;

    cout << "Maintenance costs" << endl;
    cout << "c_pm = " << d_cpm << endl;
    cout << "c_cm = " << d_ccm << endl;
    cout << "C    = " << d_C << endl << endl;

    cout << "Problem size" << endl;
    cout << "State size = " << d_nStates << endl;
    cout << "Rate size  = " << d_nRates << endl;
    cout << "Pi         = " << d_pi << endl << endl;

    cout << "Current values" << endl << endl;
    cout << setw(8) << "State1";
    cout << setw(8) << "State2";
    cout << setw(8) << "ValueA";
    cout << setw(8) << "ValueB";
    cout << setw(8) << "ExpCost";
    cout << setw(8) << "Main1";
    cout << setw(8) << "Main2";
    cout << setw(8) << "Prod1";
    cout << setw(8) << "Prod2" << endl;

    for (size_t sdx1 = 0; sdx1 != d_nStates; ++sdx1) 
    {
        for(size_t sdx2 = 0; sdx2 != d_nStates; ++sdx2) 
        {
            cout << setw(8) << to_string(sdx1);
            cout << setw(8) << to_string(sdx2);
            cout << setw(8) << d_valueA[hash(sdx1, sdx2)]; 
            cout << setw(8) << d_valueB[hash(sdx1, sdx2)]; 
            cout << setw(8) << d_expectedCost[hash(sdx1, sdx2)];
            cout << setw(8) << d_optimalMaintenance[hash(sdx1, sdx2)][0];
            cout << setw(8) << d_optimalMaintenance[hash(sdx1, sdx2)][1];
            cout << setw(8) << d_optimalProduction[hash(sdx1, sdx2)][0];
            cout << setw(8) << d_optimalProduction[hash(sdx1, sdx2)][1] << endl;
        }
    }
}