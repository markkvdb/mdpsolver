################################################################################
# R script that creates experiments                                            #
################################################################################

library(tidyverse)

grid_size = 10

base_experiment = tibble(ccm = 11.0,
                         cpm = 5.0,
                         C = 4.0,
                         nStates = 30,
                         dL = 1.0,
                         pi = 40,
                         nRates = 30,
                         mu = 1.0,
                         var = 2.0,
                         dT = 1.0,
                         minProb = 0.99,
                         beta = 0.1,
                         alpha = 1.5,
                         eps = 0.000001,
                         nUnits = 2)

experiments = base_experiment

#### Define all experiments ####

# Function to create experiment rows
create_experiments = function(variableName, values) {
  new_experiments = base_experiment[rep(1, length(values)),]
  new_experiments[[variableName]] = values 
  
  return(new_experiments)
}

# Set pi
pi_options = seq(30, 40, 50)
experiments = experiments %>%
  bind_rows(create_experiments("pi", pi_options))

# Set alpha
alpha_options = seq(0, 1, 1.5)
experiments = experiments %>%
  bind_rows(create_experiments("alpha", pi_options))

# Variance experiments
var_options = seq(0.5, 5, length.out=grid_size)
experiments = experiments %>%
  bind_rows(create_experiments("var", var_options))

# Fixed cost effect
fixed_cost_options = seq(0, 3, length.out=grid_size)
experiments = experiments %>%
  bind_rows(create_experiments("C", fixed_cost_options))


#### Output the experiments table ####

write.table(experiments, file="data/experiment_input", row.names=FALSE, col.names=FALSE)
