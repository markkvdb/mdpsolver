#include "init.ih"

#include <boost/algorithm/string.hpp>

Init::Init(num_t ccm, num_t cpm, num_t C, size_t nStates, num_t dL, size_t pi,
           size_t nRates, num_t mu, num_t var, num_t dT, num_t beta, num_t alpha, num_t eps,
           num_t minSumJump, size_t nUnits)
:
    d_nUnits(nUnits),
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
    if (d_dL != 1)
        throw("dL should be equal to 1");

    if (nUnits > 4 or nUnits < 2)
        throw("Number of units should be between 2 and 4");
    
    initialise();
}

Init::Init(string const &line) 
{
    // Split line into words seperated by spaces and put it in vector
    vector<string> args;
    boost::split(args, line, boost::is_any_of("\t "));

    if (args.size() != 15)
        throw("Wrong number of arguments supplied");

    // Assign to variables (note that num_t = double is assumed here...)
    d_ccm = stod(args[0]);
    d_cpm = stod(args[1]);
    d_C   = stod(args[2]);

    d_nStates   = stoi(args[3]);
    d_dL        = stod(args[4]);
    d_pi        = stoi(args[5]);
    d_nRates    = stoi(args[6]);

    d_mu        = stod(args[7]);
    d_var       = stod(args[8]);
    d_dT        = stod(args[9]);
    d_minSumJump= stod(args[10]);
    d_beta      = stod(args[11]);
    d_alpha     = stod(args[12]);

    d_eps       = stod(args[13]);
    d_nUnits    = stoi(args[14]);

    // Check conditions
    if (d_dL != 1)
        throw("dL should be equal to 1");

    if (d_nUnits > 4 or d_nUnits < 2)
        throw("Number of units should be between 2 and 4");

    // Initialise the rest
    initialise();
}