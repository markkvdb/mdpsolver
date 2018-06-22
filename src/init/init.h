#ifndef INCLUDED_INIT_
#define INCLUDED_INIT_

#include <vector>
#include <string>
#include <math.h>

class MDP;

using num_t = double;

class Init
{
    friend class MDP;

    // ID 
    static size_t   s_id;
    size_t const    d_id;

    // Number of units
    int d_nUnits;

    // Maintenance costs
    num_t d_ccm;
    num_t d_cpm;
    num_t d_C;

    // State space
    int  d_nStates;
    num_t   d_dL;

    // Action space
    int                 d_pi;
    int                 d_nRates;
    std::vector<num_t>  d_prodRates;
    int                 d_minWorkingUnits;

    // Probabilities
    num_t d_mu;
    num_t d_var;
    num_t d_dT;

    std::vector<std::vector<num_t>> d_prop1;
    std::vector<std::vector<num_t>> d_prop2;

    // Maximum jumps
    num_t               d_minSumJump;
    std::vector<int>    d_maxJumps;
    
    num_t d_beta;
    num_t d_alpha;
    
    std::vector<num_t> d_detRates;

    // Costs
    std::vector<num_t> d_terminalCosts;

    // Value iteration parameter
    num_t d_eps;
    
    public:
        Init() = delete;
        Init(num_t ccm, num_t cpm, num_t C, int nStates, num_t dL, int pi,
             int nRates, num_t mu, num_t var, num_t dT, num_t beta, num_t alpha, num_t eps,
             num_t minSumJump, int nUnits);
        Init(std::string const &line);

        void    printTransitionMatrix() const;
        void    printAllInfo() const;

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
    d_minWorkingUnits = ceil(static_cast<num_t>(d_pi) / (static_cast<num_t>(d_nRates)-1));
}

#endif 