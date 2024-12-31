#include "equation.h"
#include <iostream>

DiffusionEquation::DiffusionEquation(std::shared_ptr<UpdateStrategy> strategy)
    : update_strategy(std::move(strategy)) {}

void DiffusionEquation::set_strategy(std::shared_ptr<UpdateStrategy> strategy) {
    update_strategy = std::move(strategy);
}

void DiffusionEquation::update(Field& field, double dt, double dx, double D) {
    update_strategy->update(field, dt, dx, D);
}