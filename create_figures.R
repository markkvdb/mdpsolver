################################################################################
# Create R script that reads the solution for all units and creates figures    #
################################################################################

library(tidyverse)
library(reshape2)
library(stringr)

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
    mutate(`Maintenance action` = case_when(
      maintenance1 == 1 & maintenance2 == 1 ~ "Maintenance unit 1 and 2",
      maintenance1 == 1 ~ "Maintenance unit 1",
      maintenance2 == 1 ~ "Maintenance unit 2",
      TRUE ~ "No maintenance")) %>%
    mutate(`Production action` = case_when(
      production1 == production2 ~ "equal production",
      production1 > production2 ~ "production1 > production2",
      production2 > production1 ~ "production1 < production2")) %>%
    mutate(state1_max = state1 + 1,
           state2_max = state2 + 1,
           id = idx) %>%
    mutate(action = if_else(`Maintenance action` == "No maintenance", 
                            `Production action`, `Maintenance action`))
  
  optimal_policy_data = optimal_policy_data %>%
    bind_rows(optimal_policy)
  idx = idx + 1
}


# For each experiment we create the figures
for (experiment_id in 0:(n_experiments-1)) {
  optimal_policy = filter(optimal_policy_data, id == experiment_id)
  
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
                                                    fill=`Production action`)) +
    geom_rect() + theme_bw() + theme(panel.grid = element_blank(), panel.border = element_blank()) +
    scale_x_continuous(expand = c(0, 0)) +
    scale_y_continuous(expand = c(0, 0)) +
    labs(x="State unit 1", y="State unit 2")
  
  ggsave(paste("output/optimal_production_plot", experiment_id, ".pdf", sep=""), 
         opt_production_plot2, width=9, height=7)
  
  # Combine plot
  opt_action_plot = ggplot(optimal_policy, aes(xmin=state1, xmax=state1_max,
                                               ymin=state2, ymax=state2_max,
                                               fill=action)) + 
    geom_rect() + scale_colour_grey() + theme_bw() + theme(panel.grid = element_blank(), panel.border = element_blank()) +
    scale_x_continuous(expand = c(0, 0)) +
    scale_y_continuous(expand = c(0, 0)) +
    labs(x="State unit 1", y="State unit 2") + 
  
  ggsave(paste("output/optimal_action_plot", experiment_id, ".pdf", sep=""),
         width=9, height=7)
  
}


#### Average gain plots #####

avg_gain_names = list.files(experiment_dir, pattern = "^approximate_gain[0-9]*$")
avg_gain_heuristic_names = list.files(experiment_dir, pattern = "^approximate_gain_heuristics[0-9]*$")
n_experiments = length(avg_gain_names)-1
approx_gains = NULL

# Load optimal values
for (experiment_id in 0:n_experiments) {
  gains = scan(file = paste(experiment_dir, avg_gain_heuristic_names[experiment_id+1], sep="/"), what = double(), nmax = 3)
  approx_gains = approx_gains %>%
    bind_rows(tibble(id = experiment_id,
                     optimal_val=scan(file = paste(experiment_dir, avg_gain_names[experiment_id+1], sep="/"), what = double(), nmax = 1),
                     heur1_val = gains[1],
                     heur2_val = gains[2],
                     heur3_val = gains[3]))
}


# Bind with experimens to obtain corresponding value
approx_gains = approx_gains %>%
  left_join(experiments, by="id")

approx_gains_plot = function(data_sel, var_name) {
  approx_plot = ggplot(data_sel, aes_string(x=var_name, y="optimal_val")) + geom_line() +
    theme_bw() + theme(panel.grid = element_blank()) +
    scale_x_continuous(expand = c(0, 0)) +
    scale_y_continuous(expand = c(0, 0)) +
    labs(x=var_name, y="Mean cost per time")
  
  print(approx_plot)
  ggsave(paste("output/costs_", var_name, ".pdf", sep=""), 
         approx_plot, width=9, height=7)
}

# Plots of C and var
approx_gains_plot(approx_gains[8:17,], "var")
approx_gains_plot(approx_gains[18:27,], "C")






#### Create heuristic policy plots ####

# Load heuristic policy
experiment_names = list.files(experiment_dir, pattern = "^heuristic[0-9]*_policy[0-9]*.csv$")

heuristic_policy_data = NULL
for (experiment_name in experiment_names) {
  heuristic_policy = read_delim(paste(experiment_dir, experiment_name, sep="/"), delim=" ") %>%
    mutate(`Maintenance action` = case_when(
      maintenance1 == 1 & maintenance2 == 1 ~ "Maintenance unit 1 and 2",
      maintenance1 == 1 ~ "Maintenance unit 1",
      maintenance2 == 1 ~ "Maintenance unit 2",
      TRUE ~ "No maintenance")) %>%
    mutate(`Production action` = case_when(
      production1 == production2 ~ "share production",
      production1 > production2 ~ "unit 1",
      production2 > production1 ~ "unit 2")) %>%
    mutate(state1_max = state1 + 1,
           state2_max = state2 + 1,
           id = str_sub(experiment_name, 18, -5),
           heuristic = str_sub(experiment_name, 10, 10)) %>%
    mutate(action = if_else(`Maintenance action` == "No maintenance", 
                            `Production action`, `Maintenance action`))
  
  heuristic_policy_data = heuristic_policy_data %>%
    bind_rows(heuristic_policy)
}


# For each experiment we create the figures
for (heuristic_id in 1:3) {
  for (experiment_id in 0:(n_experiments-1)) {
    heuristic_policy = filter(heuristic_policy_data, id == experiment_id, heuristic == heuristic_id)
    
    # Optimal maintenance with rectangles
    opt_maintenance_plot2 = ggplot(heuristic_policy, aes(xmin=state1, xmax=state1_max,
                                                       ymin=state2, ymax=state2_max,
                                                       fill=`Maintenance action`)) +
      geom_rect() + theme_bw() + theme(panel.grid = element_blank(), panel.border = element_blank()) +
      scale_x_continuous(expand = c(0, 0)) +
      scale_y_continuous(expand = c(0, 0)) +
      labs(x="State unit 1", y="State unit 2")
    
    ggsave(paste("output/heuristic", heuristic_id,"_maintenance_plot", experiment_id, ".pdf", sep=""), 
           opt_maintenance_plot2, width=9, height=7)
    
    # Plot optimal production with rectangles
    opt_production_plot2 = ggplot(optimal_policy, aes(xmin=state1, xmax=state1_max,
                                                      ymin=state2, ymax=state2_max,
                                                      fill=`Production action`)) +
      geom_rect() + theme_bw() + theme(panel.grid = element_blank(), panel.border = element_blank()) +
      scale_x_continuous(expand = c(0, 0)) +
      scale_y_continuous(expand = c(0, 0)) +
      labs(x="State unit 1", y="State unit 2")
    
    ggsave(paste("output/heuristic", heuristic_id, "_production_plot", experiment_id, ".pdf", sep=""), 
           opt_production_plot2, width=9, height=7)
    
    # Combine both plots
    # Combine plot
    opt_action_plot = ggplot(optimal_policy, aes(xmin=state1, xmax=state1_max,
                                                 ymin=state2, ymax=state2_max,
                                                 fill=action)) + 
      geom_rect() + scale_colour_grey() + theme_bw() + theme(panel.grid = element_blank(), panel.border = element_blank()) +
      scale_x_continuous(expand = c(0, 0)) +
      scale_y_continuous(expand = c(0, 0)) +
      labs(x="State unit 1", y="State unit 2") + 
      
      ggsave(paste("output/heuristic", heuristic_id, "_action_plot", experiment_id, ".pdf", sep=""),
             width=9, height=7)
  }
}



