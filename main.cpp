#include "grid.h"
#include "time_integrator.h"
#include "update_strategy.h"
#include <cmath>
#include <iostream>

// Analytical solution for comparison
double analytical_solution(double x, double t, double D) {
    return std::exp(-M_PI * M_PI * D * t) * std::sin(M_PI * x);
}

int main() {
    const int NX = 200;
    const double DX = 1.0 / (NX - 1);
    const double D = 0.1; // Diffusion coefficient
    const double DT = 0.01 * DX * DX / (2 * D); // Time step
    const double MAX_TIME = 0.01;

    double stability = D * DT / (DX * DX);
    if (stability > 0.5) {
        std::cerr << "Warning: Stability condition violated. Ratio: " << stability << "\n";
    }


    Grid grid(NX, DX);

    // Initialize grid with the initial condition: sin(πx)
    grid.initialize([](double x) {
        return std::sin(M_PI * x);
    });

    grid.apply_boundary_conditions();

    // Create the update strategies
    auto explicit_strategy = std::make_shared<ExplicitUpdate>();
    auto implicit_strategy = std::make_shared<ImplicitUpdate>();

    // Create the equation and set the strategy
    auto equation = std::make_shared<DiffusionEquation>(explicit_strategy);

    // Change the strategy to implicit
    // equation->set_strategy(implicit_strategy);

    TimeIntegrator integrator(grid, equation);

    // Run the simulation
    integrator.run(MAX_TIME, DT, D);

    // Compare the numerical and analytical solutions
    double error = 0.0;
    for (int i = 0; i < NX; ++i) {
        double x = i * DX;
        double numerical = grid.field[i];
        double analytical = analytical_solution(x, MAX_TIME, D);
        error += std::abs(numerical - analytical);
    }
    error /= NX;

    std::cout << "Average error: " << error << std::endl;

    return 0;
}
