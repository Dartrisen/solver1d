#include "equation.h"
#include <iostream>

void DiffusionEquation::update(Field& field, double dt, double dx, double D) {
    Field old_field = field;
    for (size_t i = 1; i < field.size() - 1; ++i) {
        double d2x = (old_field[i + 1] - 2 * old_field[i] + old_field[i - 1]) / (dx * dx);
        field[i] += D * dt * d2x;
    }
}

// void DiffusionEquation::update(Field& field, double dt, double dx, double D) {
//     size_t n = field.size();
//     double alpha = D * dt / (2 * dx * dx);

//     // Tridiagonal system setup
//     std::vector<double> a(n - 1, -alpha); // Sub-diagonal
//     std::vector<double> b(n, 1 + 2 * alpha); // Main diagonal
//     std::vector<double> c(n - 1, -alpha); // Super-diagonal
//     std::vector<double> d(n); // Right-hand side

//     // Fill the RHS vector (d)
//     for (size_t i = 1; i < n - 1; ++i) {
//         d[i] = alpha * field[i - 1] + (1 - 2 * alpha) * field[i] + alpha * field[i + 1];
//     }

//     // Apply boundary conditions to d (Dirichlet example: fixed boundaries)
//     d[0] = 0.0; // Left boundary
//     d[n - 1] = 0.0; // Right boundary

//     // Solve the tridiagonal system
//     std::vector<double> new_field(n);
//     solve_tridiagonal(a, b, c, d, new_field);

//     // Update the field
//     field = new_field;
// }

// void DiffusionEquation::solve_tridiagonal(
//     const std::vector<double>& a,
//     const std::vector<double>& b,
//     const std::vector<double>& c,
//     std::vector<double>& d,
//     std::vector<double>& result
// ) {
//     size_t n = d.size();
//     std::vector<double> c_prime(n - 1);
//     std::vector<double> d_prime(n);

//     c_prime[0] = c[0] / b[0];
//     d_prime[0] = d[0] / b[0];
//     for (size_t i = 1; i < n - 1; ++i) {
//         double denom = b[i] - a[i - 1] * c_prime[i - 1];
//         c_prime[i] = c[i] / denom;
//         d_prime[i] = (d[i] - a[i - 1] * d_prime[i - 1]) / denom;
//     }
//     d_prime[n - 1] = (d[n - 1] - a[n - 2] * d_prime[n - 2]) / (b[n - 1] - a[n - 2] * c_prime[n - 2]);

//     result[n - 1] = d_prime[n - 1];
//     for (size_t i = n - 2; i < n; --i) {
//         result[i] = d_prime[i] - c_prime[i] * result[i + 1];
//     }
// }