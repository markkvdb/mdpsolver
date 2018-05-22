################################################################################
# Create R script that reads the solution for all units and creates figures    #
################################################################################

library(tidyverse)
library(reshape2)

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
optimalPolicy = read_delim("output/optimal_policy.csv", delim=" ") %>%
  mutate(`Maintenance action` = paste(maintenance_int_to_string(maintenance1), 
                                 maintenance_int_to_string(maintenance2), 
                                 sep=" ")) %>%
  mutate(`Production action` = paste(production1, production2, sep=" ")) %>%
  mutate(state1_max = state1 + 1,
         state2_max = state2 + 1)

# In wide format
optimalPolicy_wide = dcast(optimalPolicy, state1 ~ state2, value.var="Maintenance action")

# Optimal maintenance with rectangles
opt_maintenance_plot2 = ggplot(optimalPolicy, aes(xmin=state1, xmax=state1_max,
                                                 ymin=state2, ymax=state2_max,
                                                 fill=`Maintenance action`)) +
  geom_rect() + theme_bw() + theme(panel.grid = element_blank(), panel.border = element_blank()) +
  scale_x_continuous(expand = c(0, 0)) +
  scale_y_continuous(expand = c(0, 0)) +
  labs(x="State unit 1", y="State unit 2")

print(opt_maintenance_plot2)
ggsave("output/optimal_maintenance_plot.pdf", opt_maintenance_plot2, width=9, height=7)

# Plot optimal production with rectangles
opt_production_plot2 = ggplot(optimalPolicy, aes(xmin=state1, xmax=state1_max,
                                                  ymin=state2, ymax=state2_max,
                                                  fill=production1)) +
  geom_rect() + theme_bw() + theme(panel.grid = element_blank(), panel.border = element_blank()) +
  scale_x_continuous(expand = c(0, 0)) +
  scale_y_continuous(expand = c(0, 0)) +
  labs(x="State unit 1", y="State unit 2")

print(opt_production_plot2)
ggsave("output/optimal_production_plot.pdf", opt_production_plot2, width=9, height=7)

# Combine both plots