#include "time_integrator.h"

TimeIntegrator::TimeIntegrator(Grid& grid_, std::shared_ptr<Equation> eq)
    : grid(grid_), equation(std::move(eq)) {}

void TimeIntegrator::step(double dt, double D) {
    equation->update(grid.field, dt, grid.dx, D);
    grid.apply_boundary_conditions();
}

void TimeIntegrator::run(double max_time, double dt, double D) {
    double t = 0.0;
    while (t < max_time) {
        step(dt, D);
        t += dt;
    }
}