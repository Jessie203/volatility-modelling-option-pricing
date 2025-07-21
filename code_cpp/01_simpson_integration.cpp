#include <iostream>
#include <cmath>

int X=10;
double r = 0.05, sigma = 0.1, T = 0.5;

double f(double y)
{
    return X * (std::exp(-r * sigma * T)) * (std::exp(T * y));
}

// function to implement Simpsons rule from y=a to y=b with n steps
double integrate(double a, double b, int n)
{
    double sum = 0;
    double h = (b - a) / n;

    for (int i = 1; i < n; i += 2){
        sum += 4*f(a+i*h);
    }

    for (int i = 2; i < n-1; i += 2){
        sum += 2*f(a+i*h);
    }

    return sum * h/3;
}

int main()
{

    // Exact solution (calculated separately)
    double exact_solution = 12.9420298618;

    std::cout << "n\tApproximate\tExact\t\tError" << std::endl;
    for (int n = 1000; n <= 100000000; n *= 10)
    {
        double approximate = integrate(0, 1, n);
        double error = std::abs(approximate - exact_solution);

        std::cout << n << "\t" << approximate << "\t" << exact_solution << "\t" << error << std::endl;

        // If the error is within 1e-6, consider it accurate enough
        if (error < 1e-6)
        {
            std::cout << "n = " << n << " gives a solution accurate to 6 s.f." << std::endl;
            break;
        }
    }

    return 0;
}
