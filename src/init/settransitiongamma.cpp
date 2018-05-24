#include "init.ih"

#include <boost/math/distributions/gamma.hpp>

/* 
 * Set the member that contains the transition matrix
 * For each action there are two transition vectors of size nStates
 * The first one gives the probability of 'idx' jumps
 * The second one gives the probability of an instant failure for state 'idx'
 * 
 * 
 * TODO
 * correct for time length
 */


void Init::setTransitionGamma()
{
  // Create empty transition vectors
  // d_prop1 gives the probability of a jump with size idx
  // d_prop2 gives the probability of an instant failure from state idx
  
  d_prop1 = vector<vector<num_t>> (d_nRates, vector<num_t> (d_nStates, 0));
  d_prop2 = vector<vector<num_t>> (d_nRates, vector<num_t> (d_nStates, 0));
  
  // Fill the transion vectors for each action (= production rate)
  for (int adx = 0; adx != d_nRates; ++adx)
  {
    num_t const shape = d_dT * (d_mu * d_mu) / d_var;
    num_t const scale = d_detRates[adx] * (d_var / d_mu);
    
    // Find jump probabilities
    if (d_mu * d_detRates[adx] == 0)
      d_prop1[adx][0] = 1;

    else
    {
      boost::math::gamma_distribution<num_t> distribution(shape, scale);
      d_prop1[adx][0] = cdf(distribution, 0.5 * d_dL);
      
      for (int idx = 1; idx != d_nStates; ++idx)
        d_prop1[adx][idx] = cdf(distribution, (idx + 0.5) * d_dL) - cdf(distribution, (idx - 0.5) * d_dL);
    }
    
    // Probability of failure
    for (int idx = 0; idx != d_nStates; ++idx)
      d_prop2[adx][idx] = 1 - accumulate(begin(d_prop1[adx]), end(d_prop1[adx]) - idx - 1, 0.0);
  }
  
  
  
  
//   ofstream file("./jumps");
//   file << fixed << setprecision(15);
//   
//   file << "0, " << d_nRates - 1 << '\n';
//   
//   for (int idx = 0; idx < d_nStates; ++idx)
//     file << d_prop1[0][idx] << ", " << d_prop1[d_nRates - 1][idx] << '\n';
//   
//   throw;
}
