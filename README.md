# Volatility Modelling and Option Pricing

This project implements numerical methods in **C++** and **R** to price European options, estimate **implied volatility**, compute **historical volatility**, and visualize market dynamics based on real-world financial data.

It was originally developed as part of a university research project focused on derivative pricing and volatility modelling.

---

## Objectives

- Apply the **Black-Scholes model** to compute option values.
- Estimate **implied volatility** using Newton-Secant numerical methods.
- Calculate **historical volatility** from time series price data.
- Visualise time series and volatility behaviour using **R**.
- Compare theoretical values with real market approximations.

---

## Methods & Tools

### C++ Components

| File | Description |
|------|-------------|
| `01_simpson_integration.cpp` | Implements Simpson’s Rule for numerical integration. |
| `02_option_value.cpp` | Computes European call/put option value using Black-Scholes. |
| `03_virtual_function.cpp` | Object-oriented version with virtual payoff functions. |
| `04_newton_secant.cpp` | Estimates root using the Newton-Secant method. |
| `05_implied_volatility.cpp` | Computes implied volatility given market price. |
| `06_implied_volatility_loop.cpp` | Computes implied volatility across varying strike prices. |
| `07_historical_volatility.cpp` | Estimates historical volatility using stock price log returns. |

### R Components

| File | Description |
|------|-------------|
| `01_plot_timeseries.R` | Visualises stock price time series (Open, Close, Adjusted Close). |
| `02_plot_iv_vs_strike.R` | Plots implied volatility against strike price. |

---

## Sample Outputs

While original data is not included due to loss of access, output plots and computational results are discussed in the report. Sample data formats are described in code comments.

---


## References

- Black, F. & Scholes, M. (1973). *The Pricing of Options and Corporate Liabilities.*
- Natenberg, S. (1994). *Option Volatility and Pricing: Advanced Trading Strategies and Techniques.*
- Burden, R. L. (2011). *Numerical Analysis.*
- Yahoo Finance historical data.

---

## Notes

- No real data files are included; source was Yahoo Finance.
- Example plots and numerical results are reproducible if data is provided in correct format (see code comments).
- Compatible with standard C++11 compilers and base R packages.

---

## Author

This project was developed as part of my final-year coursework in mathematics and statistics, combining theoretical finance with applied computing.

> If you are a recruiter or researcher and would like to discuss the code or methods, feel free to connect via LinkedIn or email.

