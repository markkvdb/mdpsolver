#include "init.ih"

// Empty initialiser
Init::Init()
{}

Init::Init(num_t ccm, num_t cpm, num_t C, size_t nStates, num_t dL, size_t pi,
           size_t nRates, num_t mu, num_t var, num_t dT, num_t beta, num_t alpha, num_t eps,
           num_t minSumJump)
:
    d_ccm(ccm),
    d_cpm(cpm),
    d_C(C),
    d_nStates(nStates),
    d_dL(dL),
    d_pi(pi),
    d_nRates(nRates),
    d_mu(mu),
    d_var(var),
    d_dT(dT),
    d_minSumJump(minSumJump),
    d_beta(beta),
    d_alpha(alpha),
    d_eps(eps)
{
    initialise();
}