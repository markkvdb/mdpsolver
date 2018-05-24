#include "init.ih"

void Init::printAllInfo() const
{
    cout << "nUnits     = " << d_nUnits << endl;
    cout << "ccm        = " << d_ccm << endl;
    cout << "cpm        = " << d_cpm << endl;
    cout << "C          = " << d_C << endl;
    cout << "nStates    = " << d_nStates << endl;
    cout << "dL         = " << d_dL << endl;
    cout << "pi         = " << d_pi << endl;
    cout << "nRates     = " << d_nRates << endl;
    cout << "minUnits   = " << d_minWorkingUnits << endl;
    cout << "mu         = " << d_mu << endl;
    cout << "var        = " << d_var << endl;
    cout << "dT         = " << d_dT << endl;
    cout << "minSumJump = " << d_minSumJump << endl;
    cout << "beta       = " << d_beta << endl;
    cout << "alpha      = " << d_alpha << endl;
    cout << "eps        = " << d_eps << endl << endl;
}