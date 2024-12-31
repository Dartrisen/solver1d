// grid.h
#ifndef GRID_H
#define GRID_H

#include <vector>
#include <functional>

typedef std::vector<double> Field;

class Grid {
public:
    int nx;
    double dx;
    Field field;

    Grid(int nx_, double dx_);

    void initialize(std::function<double(double)> init_func);
    void apply_boundary_conditions();
    void apply_boundary_conditions_periodic();
    void print_field();
};

#endif // GRID_H