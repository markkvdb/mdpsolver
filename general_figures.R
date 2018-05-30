library(tidyverse)
library(reshape2)

g = function(u, a, b){ b + (1 - b) * u^a}
g = Vectorize(g, "u")

u_range = seq(0, 1, length.out=100)

alphas = c(0, 0.5, 1, 1.5)
betas = c(0.1)

data = NULL
for (alpha in alphas) {
  for (beta in betas) {
    data = data %>%
      bind_rows(tibble(u = u_range, g = g(u_range, alpha, beta), 
                       setting = paste("a = ", alpha, ", b = ", beta, sep="")))
  }
}

ggplot(data, aes(x = u, y = g, colour = setting)) + geom_line() + 
  theme_bw() + theme(panel.grid = element_blank()) +
  scale_x_continuous(expand = c(0, 0)) +
  scale_y_continuous(expand = c(0, 0.1)) +
  labs(x="production", y="g")

ggsave("report/figures/g.pdf", width=7, height=5)