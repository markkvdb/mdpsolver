#include "init.ih"

/*
 * This functions sets all data members to final states
 */
void Init::initialise()
{
    setActions();
    setCost();
    setTransitionGamma();
    setMaximumJump();
    setMinWorkingUnits();
}