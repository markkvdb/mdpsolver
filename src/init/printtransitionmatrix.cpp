#include "init.ih"

/* 
 * Print the transition matrix for all actions
 */

void Init::printTransitionMatrix() const
{
  if (d_prop1.size() == 0 or d_prop2.size() == 0)
    throw string("Error: transition matrices are unset (Init::printTransitionMatrix.cc)");
  
  cout << setprecision(3) << fixed;
  for (int adx = 0; adx < d_nRates; ++adx)
  {
    auto const &p1 = d_prop1[adx];
    auto const &p2 = d_prop2[adx];
    
    cout << " a = " << adx << endl;
    
    for (int idx = 0; idx < d_nStates; ++idx)
        cout << setw(7) << p1[idx];
    
    cout << " - " << accumulate(begin(p1), end(p1), 0.0) << endl;
    
    for (int idx = 0; idx < d_nStates; ++idx)
        cout << setw(7) << p2[idx];
    cout << endl << endl;
  }
}