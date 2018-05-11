#ifndef INCLUDED_INIT_
#define INCLUDED_INIT_

#include <vector>

typedef double num_t;

class Init
{
    // Maintenance costs
    num_t d_ccm;
    num_t d_cpm;
    num_t d_C;

    // State space
    size_t  d_nStates;
    num_t   d_dL;

    // Action space
    num_t               d_pi;
    size_t              d_nRates;
    std::vector<num_t>  d_prodRates;

    // Probabilities
    num_t d_mu;
    num_t d_var;
    num_t d_dT;

    std::vector<std::vector<num_t>> d_prop1;
    std::vector<std::vector<num_t>> d_prop2;

    num_t d_beta;
    num_t d_alpha;
    
    std::vector<num_t> d_detRates;

    // Costs
    std::vector<num_t> d_terminalCosts;
    
    
    public:
        Init();

        void    initialise();

    private:
        num_t   g(double prodRate) const;
        void    printTransitionMatrix() const;
        void    setTransitionGamma();
        void    setCost();
        void    setActions();
        void    setActions(num_t prodRates);
};

#endif 