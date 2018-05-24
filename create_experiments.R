################################################################################
# R script that creates experiments                                            #
################################################################################

library(tidyverse)

grid_size = 10

base_experiment = tibble(ccm = 1.0,
                         cpm = 0.2,
                         C = 0.5,
                         nStates = 50,
                         dL = 1.0,
                         pi = 60,
                         nRates = 50,
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

# Variance experiments
var_options = seq(0.1, 5, length.out = grid_size)
experiments = experiments %>%
  bind_rows(create_experiments("var", var_options))


#### Output the experiments table ####

write.table(experiments, file="data/experiment_input", row.names=FALSE, col.names=FALSE)
