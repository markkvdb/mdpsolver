#include "init.ih"

/* 
 * First the possible production rates are set
 * These are 'uniformly' distributed over the interval [0,1]
 * 
 * Second, the corresponding relative deterioration rates are set
 * 
 */

void Init::setActions()
{
  d_prodRates = bs::seq_length(0.0, 1.0, d_nRates);
  d_detRates  = vector<num_t>(d_nRates, 0);
  
  for (size_t idx = 0; idx < d_nRates; ++idx)
    d_detRates[idx] = g(d_prodRates[idx]); 
}

/*
 *   Alternatively, we only have full or no production
 */

void Init::setActions(num_t prodRate)
{
  d_prodRates = {{0.0, prodRate}};
  d_detRates  = {{g(0), g(prodRate)}};
}