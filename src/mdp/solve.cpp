#include "mdp.ih"

/*
 * Value iteration algorithm.
 * Select v_0. 
 * For each s in S, compute v_n+1.
 */

void MDP::solve()
{
    do 
    {
        // Set new values to old values
        d_valueA = d_valueB;

        // Compute the expected cost for every state and optimal production
        exp_cost();

        // Obtain new value 
        value_cost();

        // Print information
        print_all_info();

    } while(not converged());
}