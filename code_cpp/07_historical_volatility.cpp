#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>

#ifndef MVECTOR_H
#define MVECTOR_H

// Class that represents a mathematical vector
class MVector {
public:
    // constructors
    MVector() {}
    explicit MVector(int n) : v(n) {}
    MVector(int n, double x) : v(n, x) {}
    MVector(std::initializer_list<double> l) : v(l) {}

    // access element (lvalue) (see example sheet 5, q5.6)
    double &operator[](int index) {
        return v[index];
    }

    // access element (rvalue) (see example sheet 5, q5.7)
    double operator[](int index) const {
        return v[index];
    }

    int size() const { return v.size(); } // number of elements

    // Add data to the vector
    void push_back(double x) {
        v.push_back(x);
    }

private:
    std::vector<double> v;
};

#endif

double variance(const MVector &S) {
    double squareSum = 0.0;
    double DeltaS = 0.0;
    double sumLogs = 0.0;
    int n = S.size();
    for (int i = 0; i < n - 1; i++) {
        DeltaS = std::log(S[i + 1]) - std::log(S[i]);
        squareSum += DeltaS * DeltaS;
        sumLogs += DeltaS;
    }
    double results = (1.0 / (n - 1)) * squareSum - (1.0 / (n * n - n)) * sumLogs * sumLogs;

    return sqrt(n*results);
}

int main() {
    std::ifstream input("output.txt");
    MVector stockPrices; // Use MVector to store all data

    if (!input) {
        std::cout << "Could not open file for reading" << std::endl;
        return 1;
    }

    double value;
    while (input >> value) {
        // Assuming all values are in the file
        stockPrices.push_back(value);
    }

    input.close();

    // Print all values in the vector
    for (int i = 0; i < stockPrices.size(); i++) {
        std::cout << stockPrices[i] << " ";
    }

    // Calculate and print the variance
    double stockVariance = variance(stockPrices);
    std::cout << "\nVariance: " << stockVariance << std::endl;

    return 0;
}
