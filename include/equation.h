#ifndef EQUATION_H
#define EQUATION_H

#include "grid.h"

class Equation {
public:
    virtual void update(Field& field, double dt, double dx, double D) = 0;
    virtual ~Equation() = default;
};

class DiffusionEquation : public Equation {
public:
    void update(Field& field, double dt, double dx, double D) override;
private:
    void solve_tridiagonal(
        const std::vector<double>& a,
        const std::vector<double>& b,
        const std::vector<double>& c,
        std::vector<double>& d,
        std::vector<double>& result
    );
};

#endif // EQUATION_H