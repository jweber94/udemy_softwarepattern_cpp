#include <iostream>
#include <vector>
#include <complex>
#include <tuple>
#include <cmath>
#include <limits>
using namespace std;

struct DiscriminantStrategy
{
    virtual double calculate_discriminant(double a, double b, double c) = 0;
};

struct OrdinaryDiscriminantStrategy : DiscriminantStrategy
{
    double calculate_discriminant(double a, double b, double c) {
        return pow(b, 2) - 4 * a * c;
    }
};

struct RealDiscriminantStrategy : DiscriminantStrategy
{
    double calculate_discriminant(double a, double b, double c) {
        double result = pow(b, 2) - 4 * a * c;
        if (result <= 0) {
            return numeric_limits<double>::quiet_NaN();
        }
        return result;
    }
};

class QuadraticEquationSolver
{
    DiscriminantStrategy& strategy;
public:
    QuadraticEquationSolver(DiscriminantStrategy& strategy) : strategy(strategy) {}

    tuple<complex<double>, complex<double>> solve(double a, double b, double c)
    {
        std::complex<double> posResult;
        std::complex<double> negResult;

        double tmpDiscriminant = strategy.calculate_discriminant(a, b, c);
        //if (std::isnan(tmpDiscriminant)) {
        //    return { tmpDiscriminant , tmpDiscriminant };
        //}
        posResult = ((-b) + sqrt(std::complex<double>(tmpDiscriminant, 0.))) / (2 * a);
        negResult = ((-b) - sqrt(std::complex<double>(tmpDiscriminant, 0.))) / (2 * a);

        return { posResult, negResult };
    }
};

int main() {
    OrdinaryDiscriminantStrategy ods;
    RealDiscriminantStrategy rds;

    QuadraticEquationSolver odsSolver(ods);
    QuadraticEquationSolver rdsSolver(rds);

    double a = 5.;
    double b = 6.;
    double c = 40000.;

    auto ordinaryResult = odsSolver.solve(a, b, c);
    std::cout << "Ordinary Solver result is " << std::get<0>(ordinaryResult) << "; " << std::get<1>(ordinaryResult) << std::endl;

    auto realResult = rdsSolver.solve(a, b, c);
    std::cout << "Real Solver result is " << std::get<0>(realResult) << "; " << std::get<1>(realResult) << std::endl;

	return 0;
}