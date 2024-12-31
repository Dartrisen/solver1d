#ifndef EQUATION_H
#define EQUATION_H

#include "grid.h"
#include "update_strategy.h"

class Equation {
public:
    virtual void update(Field& field, double dt, double dx, double D) = 0;
    virtual ~Equation() = default;
};

class DiffusionEquation : public Equation {
public:
    explicit DiffusionEquation(std::shared_ptr<UpdateStrategy> strategy);

    void set_strategy(std::shared_ptr<UpdateStrategy> strategy);
    void update(Field& field, double dt, double dx, double D) override;

private:
    std::shared_ptr<UpdateStrategy> update_strategy;
};

#endif // EQUATION_H