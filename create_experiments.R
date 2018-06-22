################################################################################
# R script that creates experiments                                            #
################################################################################

library(tidyverse)

grid_size = 30
problem_size = 25

base_experiment = tibble(ccm = 100,
                         cpm = 0.2 * ccm,
                         C = 0.4 * ccm,
                         nStates = problem_size + 1,
                         dL = 1.0,
                         pi = problem_size,
                         nRates = problem_size + 1,
                         mu = 1.0,
                         var = 1.0,
                         dT = 1.0,
                         minProb = 0.99,
                         beta = 0.1,
                         alpha = 1.5,
                         eps = 0.0000001,
                         nUnits = 2)

experiments = base_experiment

#### Define all experiments ####

# Function to create experiment rows
create_experiments = function(variableName, values) {
  new_experiments = base_experiment[rep(1, length(values)),]
  new_experiments[[variableName]] = values 
  
  return(new_experiments)
}

# Variance experiments
var_options = seq(0.5, 5, length.out=grid_size)
experiments = experiments %>%
  bind_rows(create_experiments("var", var_options))

# Fixed cost effect
fixed_cost_options = seq(0, 200, length.out=grid_size)
experiments = experiments %>%
  bind_rows(create_experiments("C", fixed_cost_options))

# Preventive effect 
preventive_cost_options = seq(0, 100, length.out=grid_size)
experiments = experiments %>%
  bind_rows(create_experiments("cpm", preventive_cost_options))

# Beta
b_options = seq(0, 1, length.out=grid_size)
experiments = experiments %>%
  bind_rows(create_experiments("beta", b_options))

# Alpha
alpha_options = seq(0, 3, length.out=grid_size)
experiments = experiments %>%
  bind_rows(create_experiments("alpha", alpha_options))

# Pi
pi_options = seq(20, 50, by=5)
experiments = experiments %>%
  bind_rows(create_experiments("pi", pi_options))

# Set alpha
alpha_options = c(0, 0.5, 1)
experiments = experiments %>%
  bind_rows(create_experiments("alpha", alpha_options))


#### Output the experiments table ####

write.table(experiments, file="data/experiment_input", row.names=FALSE, col.names=FALSE)