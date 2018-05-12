#include "mdp.ih"

void MDP::print_all_info()
{
    cout << "Maintenance costs" << endl;
    cout << "c_pm = " << d_cpm << endl;
    cout << "c_cm = " << d_ccm << endl;
    cout << "C    = " << d_C << endl << endl;

    cout << "Problem size" << endl;
    cout << "State size = " << d_nStates << endl;
    cout << "Rate size  = " << d_nRates << endl;
    cout << "Pi         = " << d_pi << endl << endl;

    cout << "Current values" << endl;
    cout << "ValueA  = ";
    for (auto const &val: d_valueA)
        cout << val << ' ';
    cout << endl;
    cout << "ValueB  = ";
    for (auto const &val: d_valueB)
        cout << val << ' ';
    cout << endl;
    cout << "Exp cost = ";
    for (auto const &val: d_expectedCost)
        cout << val << ' ';
    cout << endl << endl;
}