#include <iostream>
#include <cmath>
#include <algorithm> // For std::max function

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
    double marketValue = 0.05;
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


int main()
{
    double result;
    double S = 1;
    double X = 1;
    double T = 0.5;
    double r = 0.05;
    double sigma0 = 0.1; // Adjusted initial guess
    double sigma1 = 0.2; // Adjusted initial guess
    double tol = 1e-6;
    int maxiter = 100000; // Increased maximum iterations

    CallOption callOption(X);

    bool success = NewtonSecant(result, sigma0,sigma1,  tol, maxiter, S,X, r, T,callOption);

    if (success) {
        std::cout << "Root found: " << result << std::endl;
    } else {
        std::cout << "Root not found within maximum iterations." << std::endl;
    }

    return 0;
}
