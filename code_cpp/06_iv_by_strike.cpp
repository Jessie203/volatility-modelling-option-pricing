#include <iostream>
#include <cmath>
#include <algorithm> // For std::max function
#include <fstream>

// Payoff class remains the same
class Payoff {
public:
    virtual double operator()(double y) = 0;
    virtual ~Payoff() {}
};

// CallOption and PutOption classes remain the same

class OptionPricer {
private:
    double r; // Risk-free interest rate
    double sigma; // Volatility
    double T; // Time to expiration
    int n; // Number of steps for numerical integration

    // Helper function for integration
    double f_object(double x, double y, double X, double k, Payoff &payoff) {
        double V = std::max(X * std::exp(y) - X, 0.0);
        double B = exp((-pow(x - y, 2) / (2 * pow(sigma, 2) * T)) + 0.5 * k * y);
        return B * V;
    }

    // Simpson's rule integration
    double integrate(double a, double b, double x, double X, double k, Payoff &payoff) {
        double sum = 0;
        double h = (b - a) / n;

        sum += 0.5 * (f_object(x, a, X, k, payoff) + f_object(x, b, X, k, payoff));

        for (int i = 1; i < n; i++) {
            sum += f_object(x, a + i * h, X, k, payoff) * (i % 2 == 0 ? 2 : 4);
        }
        
        return sum * h / 3;
    }

public:
    // Constructor
    OptionPricer(double r_, double sigma_, double T_, int n_) : r(r_), sigma(sigma_), T(T_), n(n_) {}

    // Method to calculate the option value
    double optionValue(double S, double X, Payoff &payoff) {
        double x = std::log(S/X);
        double k = 2 * r / (sigma * sigma) - 1;
        double A = (1 / sqrt(2 * sigma * sigma * M_PI * T)) * (std::exp(-0.5 * k * x - 0.125 * sigma * sigma * k * k * T - r * T));
        double value = integrate(-10, 10, x, X, k, payoff);
        return A * value;
    }
};

double g(double S,double X,double r,double sigma, double T,Payoff &payoff)
{
    double bidprice = 21.95;
    double askprice = 22.1;
    double marketValue = 1.425;
    int n = 1000;
    OptionPricer pricer(r, sigma, T, n);
    double optionValue = pricer.optionValue(S,X,payoff);
    return optionValue - marketValue;

}

bool NewtonSecant(double &result, double sigma0, double sigma1, double tol, int
maxiter, double S,double X,double r, double T,Payoff &payoff)
{
int i;
double sigma;
for (i=0; i<maxiter; i++)
{
sigma = sigma1 - g(S, X,r,sigma1, T, payoff)*(sigma1-sigma0)/
(g(S, X,r,sigma1, T, payoff)-g(S, X,r,sigma0, T, payoff));
if (std::abs(g(S, X,r,sigma, T, payoff))<tol) break;
sigma0=sigma1;
sigma1=sigma;
}
result = sigma;

if (i==maxiter)
return false;
else return true;
}

class CallOption : public Payoff {
private:
    double X;

public:
    CallOption(double X_) : X(X_) {}
    double operator()(double y) {
        return std::max(X * std::exp(y) - X, 0.0);
    }
};


int main() {
    double S = 30.23;
    double T = 0.1205;
    double r = 0.002;
    double sigma0 = 0.1; // Adjusted initial guess
    double sigma1 = 0.2; // Adjusted initial guess
    double tol = 1e-6;
    int maxiter = 1000; // Increased maximum iterations

    // Output file
    std::ofstream outputFile("implied_volatility_results.csv");
    outputFile << "Strike Price,Implied Volatility\n"; // Header

    // Loop over a range of strike prices
    for (double X = 29.0; X <= 35.0; X += 1.0) {
        CallOption callOption(X);

        double result; // Implied volatility result
        bool success = NewtonSecant(result, sigma0, sigma1, tol, maxiter, S, X, r, T, callOption);

        if (success) {
            // Print the result to the console
            std::cout << "Strike Price: " << X << ", Implied Volatility: " << result << std::endl;

            // Write the result to the file
            outputFile << X << "," << result << "\n";
        } else {
            std::cout << "Root not found within maximum iterations for Strike Price: " << X << std::endl;
        }
    }

    // Close the output file
    outputFile.close();

    return 0;
}
