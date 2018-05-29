################################################################################
# Create R script that reads the solution for all units and creates figures    #
################################################################################

library(tidyverse)
library(reshape2)

source("create_experiments.R")
experiments = mutate(experiments, id = seq(0, nrow(experiments)-1))

experiment_dir = "output"

#### Create optimal policy plots ####

# Function to map integer maintenance to string
maintenance_int_to_string = function(maintenance_int) {
  if (maintenance_int == 0) {
    return("DN")
  } else {
    return("M")
  }
}
maintenance_int_to_string = Vectorize(maintenance_int_to_string, "maintenance_int")

# Load optimal policy
experiment_names = list.files(experiment_dir, pattern = "^optimal_policy[0-9]*.csv$")
n_experiments = length(experiment_names)
idx = 0

optimal_policy_data = NULL
for (experiment_name in experiment_names) {
  optimal_policy = read_delim(paste(experiment_dir, experiment_name, sep="/"), delim=" ") %>%
    mutate(`Maintenance action` = paste(maintenance_int_to_string(maintenance1), 
                                        maintenance_int_to_string(maintenance2), 
                                        sep=" ")) %>%
    mutate(`Production action` = paste(production1, production2, sep=" ")) %>%
    mutate(state1_max = state1 + 1,
           state2_max = state2 + 1,
           id = idx)
  
  optimal_policy_data = optimal_policy_data %>%
    bind_rows(optimal_policy)
  idx = idx + 1
}


# For each experiment we create the figures
for (experiment_id in 0:(n_experiments-1)) {
  optimal_policy = filter(optimal_policy_data, id == experiment_id)
  
  # In wide format
  optimal_policy_wide = dcast(optimal_policy, state1 ~ state2, value.var="Maintenance action")
  
  # Optimal maintenance with rectangles
  opt_maintenance_plot2 = ggplot(optimal_policy, aes(xmin=state1, xmax=state1_max,
                                                     ymin=state2, ymax=state2_max,
                                                     fill=`Maintenance action`)) +
    geom_rect() + theme_bw() + theme(panel.grid = element_blank(), panel.border = element_blank()) +
    scale_x_continuous(expand = c(0, 0)) +
    scale_y_continuous(expand = c(0, 0)) +
    labs(x="State unit 1", y="State unit 2")
  
  ggsave(paste("output/optimal_maintenance_plot", experiment_id, ".pdf", sep=""), 
         opt_maintenance_plot2, width=9, height=7)
  
  # Plot optimal production with rectangles
  opt_production_plot2 = ggplot(optimal_policy, aes(xmin=state1, xmax=state1_max,
                                                    ymin=state2, ymax=state2_max,
                                                    fill=production1)) +
    geom_rect() + theme_bw() + theme(panel.grid = element_blank(), panel.border = element_blank()) +
    scale_x_continuous(expand = c(0, 0)) +
    scale_y_continuous(expand = c(0, 0)) +
    labs(x="State unit 1", y="State unit 2")
  
  ggsave(paste("output/optimal_production_plot", experiment_id, ".pdf", sep=""), 
         opt_production_plot2, width=9, height=7)
  
  # Combine both plots
}


#### Average gain plots #####

avg_gain_names = list.files(experiment_dir, pattern = "^approximate_gain[0-9]*$")
n_experiments = length(avg_gain_names)-1
approx_gains = NULL

for (experiment_id in 0:n_experiments) {
  approx_gains = approx_gains %>%
    bind_rows(tibble(id = experiment_id, 
                     value=scan(file = paste(experiment_dir, avg_gain_names[1], sep="/"), what = double(), nmax = 1)))
}

# Bind with experimens to obtain corresponding value
approx_gains = approx_gains %>%
  left_join(experiments, by="id")

approx_gains_plot = function(data_sel, var_name) {
  approx_plot = ggplot(data_sel, aes_string(x=var_name, y="value")) + geom_line() +
    theme_bw() + theme(panel.grid = element_blank()) +
    scale_x_continuous(expand = c(0, 0)) +
    scale_y_continuous(expand = c(0, 0)) +
    labs(x=var_name, y="Mean cost per time")
  
  print(approx_plot)
  ggsave(paste("output/costs_", var_name, ".pdf", sep=""), 
         opt_production_plot2, width=9, height=7)
}

# var plot
approx_gains_plot(approx_gains[2:11,], "var")
approx_gains_plot(approx_gains[12:21,], "C")



