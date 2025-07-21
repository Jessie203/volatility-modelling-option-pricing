# Install and load required packages if not already installed
# install.packages("ggplot2")
# install.packages("dplyr")
library(ggplot2)
library(dplyr)

# Convert the 'Date' column to Date format
df$Date <- as.Date(df$Date)

# Create a time series plot using ggplot2
ggplot(df, aes(x = Date)) +
  geom_line(aes(y = Close, color = 'Close'), size = 1, linetype = 'solid') +
  geom_line(aes(y = Open, color = 'Open'), size = 1, linetype = 'solid') +
  geom_line(aes(y = `Adj.Close`, color = 'Adj Close'), size = 1, linetype = 'solid') +

  labs(title = 'Time Series of Prices and Volume',
       x = 'Date',
       y = 'Price/Volume') +
  scale_y_continuous(labels = scales::comma) +  # Format y-axis labels
  theme_minimal() +
  scale_color_manual(values = c('Close' = 'blue', 'Open' = 'red', 'Adj Close' = 'green')) +

  theme(legend.position = 'bottom')  # Move the legend to the bottom
