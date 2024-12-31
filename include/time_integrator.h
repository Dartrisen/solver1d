#ifndef TIME_INTEGRATOR_H
#define TIME_INTEGRATOR_H

#include "grid.h"
#include "equation.h"
#include <memory>

class TimeIntegrator {
public:
    TimeIntegrator(Grid& grid_, std::shared_ptr<Equation> eq);

    void step(double dt, double D);
    void run(double max_time, double dt, double D);

private:
    Grid& grid;
    std::shared_ptr<Equation> equation;
};

#endif // TIME_INTEGRATOR_H