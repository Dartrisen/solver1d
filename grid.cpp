#include "grid.h"
#include <vector>
#include <functional>
#include <iostream>

typedef std::function<double(double)> Function;

Grid::Grid(int nx_, double dx_)
    : nx(nx_), dx(dx_), field(nx_, 0.0) {}

void Grid::initialize(Function init_func) {
    for (int i = 0; i < nx; ++i) {
        double x = i * dx;
        field[i] = init_func(x);
    }
}

void Grid::apply_boundary_conditions() {
    field[0] = 0.0;
    field[nx - 1] = 0.0;
}

void Grid::print_field() {
    for (const auto& value : field) {
        std::cout << value << " ";
    }
}