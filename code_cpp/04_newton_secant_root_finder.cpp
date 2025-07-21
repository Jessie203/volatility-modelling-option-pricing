#include <iostream>
#include <cmath>

double newton_secant_f(double x)
{
    return x*x - 2;
}

bool NewtonSecant(double &result, double x0, double x1, double tol, int
maxiter)
{
int i;
double x;
for (i=0; i<maxiter; i++)
{
x = x1 - newton_secant_f(x1)*(x1-x0)/
(newton_secant_f(x1)-newton_secant_f(x0));
if (std::abs(newton_secant_f(x))<tol) break;
x0=x1;
x1=x;
}
result = x;

if (i==maxiter)
return false;
else return true;
}

int main() {
    double result;
    double x0 = 1.0;
    double x1 = 2.0;
    double tol = 1e-6;
    int maxiter = 100;

    bool success = NewtonSecant(result, x0, x1, tol, maxiter);

    if (success) {
        std::cout << "Root found: " << result << std::endl;
    } else {
        std::cout << "Root not found within maximum iterations." << std::endl;
    }

    return 0;
}
