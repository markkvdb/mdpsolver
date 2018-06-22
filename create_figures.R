################################################################################
# Create R script that reads the solution for all units and creates figures    #
################################################################################

library(tidyverse)
library(reshape2)
library(stringr)
library(ggthemes)

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
      maintenance1 == 1 & maintenance2 == 1 ~ "12",
      maintenance1 == 1 ~ "1",
      maintenance2 == 1 ~ "2",
      TRUE ~ "MNA")) %>%
    mutate(production1 = production1 / problem_size,
           production2 = production2 / problem_size) %>%
    mutate(`Production action` = case_when(
      production1 == production2 ~ "=",
      production1 > production2 ~ "+",
      production2 > production1 ~ "-")) %>%
    mutate(state1_max = state1 + 1,
           state2_max = state2 + 1,
           id = as.numeric(str_extract(experiment_name, "[0-9]+"))) %>%
    mutate(action = if_else(`Maintenance action` == "MNA", 
                            `Production action`, `Maintenance action`))
  
  optimal_policy_data = optimal_policy_data %>%
    bind_rows(optimal_policy)
}


# For each experiment we create the figures
for (experiment_id in 0:(n_experiments-1)) {
  optimal_policy = filter(optimal_policy_data, id == experiment_id)
  
  # Plot optimal production with rectangles
  opt_production_plot2 = ggplot(optimal_policy, aes(xmin=state1, xmax=state1_max,
                                                    ymin=state2, ymax=state2_max,
                                                    fill=production1)) +
    geom_rect() + theme_bw() + theme(panel.grid = element_blank(), panel.border = element_blank()) +
    scale_fill_continuous(low="#FFFFFF", high="#000000", guide="colourbar") + 
    scale_x_continuous(expand = c(0, 0)) +
    scale_y_continuous(expand = c(0, 0)) +
    labs(x="State unit 1", y="State unit 2") +
    guides(fill=guide_legend(title="Unit 1 production"))
  
  ggsave(paste("output/optimal_production_plot", experiment_id, ".pdf", sep=""), 
         opt_production_plot2, width=9, height=7)
  
  # Combine plot
  opt_action_plot = ggplot(optimal_policy) + 
    geom_rect(aes(xmin=state1, xmax=state1_max, ymin=state2, ymax=state2_max,
                  fill=action), alpha=0.5) + 
    scale_colour_grey() + theme_bw() + theme(panel.grid = element_blank(), panel.border = element_blank()) +
    geom_text(aes(x=state1 + (state1_max - state1)/2, y=state2 + (state2_max - state2)/2, label=action), size=3) + 
    scale_x_continuous(expand = c(0, 0)) +
    scale_y_continuous(expand = c(0, 0)) +
    labs(x="State unit 1", y="State unit 2") +
    scale_fill_manual(values=c("+" = "#6A6A6A", "-" = "#C8C8C8", "=" = "#989898",
                               "1" = "#FFFFFF", "2" = "#FFFFFF", "12" = "#FFFFFF"))
  
  ggsave(paste("output/optimal_action_plot", experiment_id, ".pdf", sep=""),
         width=9, height=7)
  
}


#### Average gain plots #####

avg_gain_names = list.files(experiment_dir, pattern = "^approximate_gain[0-9]*$")
avg_gain_heuristic_names = list.files(experiment_dir, pattern = "^approximate_gain_heuristics[0-9]*$")
n_experiments = length(avg_gain_names)-1
approx_gains = NULL
optimal_gains = NULL

# Load optimal values
for (avg_gain_name in avg_gain_heuristic_names) {
  gains = scan(file = paste(experiment_dir, avg_gain_name, sep="/"), what = double(), nmax = 3)
  approx_gains = approx_gains %>%
    bind_rows(tibble(id = as.numeric(str_extract(avg_gain_name, "[0-9]*$")),
                     heur1_val = gains[1],
                     heur2_val = gains[2],
                     heur3_val = gains[3]))
}
for (avg_gain_name in avg_gain_names) {
  gain = scan(file = paste(experiment_dir, avg_gain_name, sep="/"), what = double(), nmax = 1)
  optimal_gains = optimal_gains %>%
    bind_rows(tibble(id = as.numeric(str_extract(avg_gain_name, "[0-9]*$")),
                     optimal_val = gain))
}
approx_gains = left_join(approx_gains, optimal_gains, by="id")

# Bind with experimens to obtain corresponding value
approx_gains = approx_gains %>%
  left_join(experiments, by="id") %>%
  arrange(id)

approx_gains_plot = function(data_sel, var_name) {
  approx_plot = ggplot(data_sel, aes_string(x=var_name, y="optimal_val")) + geom_point() +
    theme_bw() + theme(panel.grid = element_blank()) +
    scale_x_continuous(expand = c(0, 0)) +
    scale_y_continuous(expand = c(0, 0)) +
    labs(x=var_name, y="Mean cost per time")
  
  print(approx_plot)
  ggsave(paste("output/costs_", var_name, ".pdf", sep=""), 
         approx_plot, width=9, height=7)
}

# Plots of C and var
approx_gains_plot(approx_gains[2:101,], "var")
approx_gains_plot(approx_gains[102:201,], "C")




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
           id = str_extract(experiment_name, "([0-9]+){2}"),
           heuristic = str_extract(experiment_name, "([0-9]+){1}")) %>%
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
    opt_production_plot2 = ggplot(heuristic_policy, aes(xmin=state1, xmax=state1_max,
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
    opt_action_plot = ggplot(heuristic_policy, aes(xmin=state1, xmax=state1_max,
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



