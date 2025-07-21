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
class CallOption : public Payoff {
private:
    double X;

public:
    CallOption(double X_) : X(X_) {}
    double operator()(double y) {
        return std::max(X * std::exp(y) - X, 0.0);
    }
};

class PutOption : public Payoff {
private:
    double X;

public:
    PutOption(double X_) : X(X_) {}
    double operator()(double y) {
        return std::max(X - X * std::exp(y) , 0.0);
    }
};

int main() {
    // Parameters for option pricing
    double S = 100.0; // Current stock price
    double X = 100.0; // Strike price
    double r = 0.05; // Risk-free interest rate
    double sigma = 0.1; // Volatility
    double T = 0.5; // Time to expiration
    int n = 1000; // Number of steps for numerical integration 
    // Create an instance of the pricer 
    OptionPricer pricer(r, sigma, T, n); 

    // Create a payoff instance, for example, a CallOption 
    CallOption callPayoff(X); // Calculate the call option value 
    double callValue = pricer.optionValue(S, X, callPayoff); 
    std::cout << "The value of the call option is: " << callValue << std::endl; 
    // Similarly for a put option 
    PutOption putPayoff(X); 
    double putValue = pricer.optionValue(S, X, putPayoff);
    std::cout << "The value of the put option is: " << putValue << std::endl; 


    return 0; 
    }
