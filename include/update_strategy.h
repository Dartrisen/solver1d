#ifndef UPDATE_STRATEGY_H
#define UPDATE_STRATEGY_H

#include <vector>

typedef std::vector<double> Field;

class UpdateStrategy {
public:
    virtual void update(Field& field, double dt, double dx, double D) = 0;
    virtual ~UpdateStrategy() = default;
};

// Explicit update strategy
class ExplicitUpdate : public UpdateStrategy {
public:
    void update(Field& field, double dt, double dx, double D) override;
};

// Implicit update strategy
class ImplicitUpdate : public UpdateStrategy {
public:
    void update(Field& field, double dt, double dx, double D) override;
private:
    void solve_tridiagonal(
        const std::vector<double>& a,
        const std::vector<double>& b,
        const std::vector<double>& c,
        const std::vector<double>& d,
        std::vector<double>& result);
};

#endif // UPDATE_STRATEGY_H