#include "update_strategy.h"
#include <vector>

class ExplicitUpdate : public UpdateStrategy {
public:
    void update(Field& field, double dt, double dx, double D) override {
        Field old_field = field;
        for (size_t i = 1; i < field.size() - 1; ++i) {
            double d2x = (old_field[i + 1] - 2 * old_field[i] + old_field[i - 1]) / (dx * dx);
            field[i] += dt * D * d2x;
        }
    }
};

class ImplicitUpdate : public UpdateStrategy {
public:
    void update(Field& field, double dt, double dx, double D) override {
        size_t n = field.size();
        std::vector<double> a(n - 2, -D * dt / (2 * dx * dx));
        std::vector<double> b(n - 2, 1 + D * dt / (dx * dx));
        std::vector<double> c(n - 2, -D * dt / (2 * dx * dx));
        std::vector<double> d(n - 2);

        for (size_t i = 1; i < n - 1; ++i) {
            d[i - 1] = field[i] + D * dt / (2 * dx * dx) * (field[i + 1] - 2 * field[i] + field[i - 1]);
        }

        std::vector<double> result(n - 2);
        solve_tridiagonal(a, b, c, d, result);

        for (size_t i = 1; i < n - 1; ++i) {
            field[i] = result[i - 1];
        }
    }
};

void solve_tridiagonal(
    const std::vector<double>& a,
    const std::vector<double>& b,
    const std::vector<double>& c,
    const std::vector<double>& d,
    std::vector<double>& result) {
    size_t n = b.size();
    std::vector<double> c_prime(n, 0.0);
    std::vector<double> d_prime(n, 0.0);

    // Forward sweep
    c_prime[0] = c[0] / b[0];
    d_prime[0] = d[0] / b[0];

    for (size_t i = 1; i < n; ++i) {
        double m = b[i] - a[i - 1] * c_prime[i - 1];
        c_prime[i] = c[i] / m;
        d_prime[i] = (d[i] - a[i - 1] * d_prime[i - 1]) / m;
    }

    // Back substitution
    result[n - 1] = d_prime[n - 1];
    for (size_t i = n - 2; i < n; --i) {
        result[i] = d_prime[i] - c_prime[i] * result[i + 1];
    }
}
