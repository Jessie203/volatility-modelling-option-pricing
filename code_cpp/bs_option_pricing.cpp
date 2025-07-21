#include <iostream>
#include <cmath>

double payoff(double y, double X)
{
    return std::max(X * std::exp(y) - X, 0.0);
};

double A(double x, double r, double sigma,double T, double k)
{
    return (1/sqrt(2*sigma*sigma* M_PI*T))*(std::exp(-0.5*k*x-0.125*sigma*sigma*k*k*T-r*T));
};

double B(double x, double y, double sigma, double T, double k)
{
    return exp((-pow(x - y, 2) / (2 * pow(sigma, 2) * T)) + 0.5 * k * y);
}


double f(double x,double y,double X,double r,
double sigma,double T,double k)
{
    return B(x,y,sigma,T,k)*payoff(y,X);
}

// function to implement Simpsons rule from y=a to y=b with n steps
double integrate(double a,double b,int n,double x,
double X,double r,double sigma,double T,double k)
{
    double sum = 0;
    double h = (b - a) / n;

    for (int i = 1; i < n; i += 2){
        sum += 4*f(x, a+i*h,  X, r, sigma, T,k);
    }

    for (int i = 2; i < n-1; i += 2){
        sum += 2*f(x, a+i*h,  X, r, sigma, T,k);
    }

    return sum * h/3;
}


int main()
{
    double exact_solution = 7.369373;

    double X = 100;
    double r = 0.06;
    double sigma = 0.2;
    double T = 0.75;
    double S_0 = 97;
   

    double x = std::log(S_0/X);
    double k = 2*r/(sigma*sigma)-1;

    std::cout << "n\tApproximate\tExact\t\tError" << std::endl;
    for (int n = 100; n <= 1000000; n *= 10)
    {
        double value = integrate(-10,10,n,x,X,r,sigma,T,k);
        double approximate = A(x,r,sigma,T,k)*value;
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
