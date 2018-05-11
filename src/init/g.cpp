#include "init.ih"

/*
 * Define the function g
 */

num_t Init::g(double prodRate) const
{
  return d_beta + (1 - d_beta) * pow(prodRate, d_alpha);
}