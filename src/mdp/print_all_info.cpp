#include "mdp.ih"

void MDP::print_all_info() const
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

    int idxState = 0;

    for (int sdx1 = 0; sdx1 != d_nStates; ++sdx1) 
    {
        for(int sdx2 = 0; sdx2 != d_nStates; ++sdx2) 
        {
            cout << setw(8) << to_string(sdx1);
            cout << setw(8) << to_string(sdx2);
            cout << setw(8) << d_valueA[idxState]; 
            cout << setw(8) << d_valueB[idxState]; 
            cout << setw(8) << d_expectedCost[idxState];
            cout << setw(8) << d_optimalMaintenance[idxState][0];
            cout << setw(8) << d_optimalMaintenance[idxState][1];
            cout << setw(8) << d_optimalProduction[idxState][0];
            cout << setw(8) << d_optimalProduction[idxState][1] << endl;
            ++idxState;
        }
    }
}