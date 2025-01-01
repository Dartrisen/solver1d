// grid.h
#ifndef GRID_H
#define GRID_H

#include <vector>
#include <functional>

typedef std::vector<double> Field;
typedef std::function<double(double)> Function;

class Grid {
public:
    int nx;
    double dx;
    Field field;

    Grid(int nx_, double dx_);

    void initialize(Function init_func);
    void apply_boundary_conditions();
    void print_field();
};

#endif // GRID_H