df<-read.csv("implied_volatility_results.csv")
plot(df$Strike.Price,df$Implied.Volatility, xlab ="Strike Price", ylab = "Implied Volatility")
lines(df$Strike.Price,df$Implied.Volatility)
