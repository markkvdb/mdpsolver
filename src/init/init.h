#ifndef INCLUDED_INIT_
#define INCLUDED_INIT_

#include <vector>
#include <math.h>

class MDP;

typedef double num_t;

class Init
{
    friend class MDP;

    // Maintenance costs
    num_t d_ccm;
    num_t d_cpm;
    num_t d_C;

    // State space
    size_t  d_nStates;
    num_t   d_dL;

    // Action space
    size_t              d_pi;
    size_t              d_nRates;
    std::vector<num_t>  d_prodRates;
    size_t              d_minWorkingUnits;

    // Probabilities
    num_t d_mu;
    num_t d_var;
    num_t d_dT;

    std::vector<std::vector<num_t>> d_prop1;
    std::vector<std::vector<num_t>> d_prop2;

    // Maximum jumps
    num_t               d_minSumJump;
    std::vector<size_t> d_maxJumps;
    

    num_t d_beta;
    num_t d_alpha;
    
    std::vector<num_t> d_detRates;

    // Costs
    std::vector<num_t> d_terminalCosts;

    // Value iteration parameter
    num_t d_eps;
    
    
    public:
        Init();
        Init(num_t ccm, num_t cpm, num_t C, size_t nStates, num_t dL, size_t pi,
             size_t nRates, num_t mu, num_t var, num_t dT, num_t beta, num_t alpha, num_t eps,
             num_t minSumJump);

        void    printTransitionMatrix() const;

    private:
        void    initialise();
        num_t   g(double prodRate) const;
        void    setTransitionGamma();
        void    setCost();
        void    setActions();
        void    setActions(num_t prodRates);
        void    setMaximumJump();
        void    setMinWorkingUnits();
};

inline void Init::setMinWorkingUnits()
{
    d_minWorkingUnits = ceil(d_pi / (d_nRates-1));
}

#endif 