#include "a1_solution.hpp"
#include <cmath>

// User constants
constexpr double m = 1;
constexpr double E0 = 1;
constexpr double k = 0.1;
constexpr double omega = 2;
constexpr double dt = 0.005;

// Numerical and derived constants
const double sqrt2 = std::sqrt(2);
constexpr int steps_for_two_cycles = 2 * 2 * M_PI / dt / omega;

auto force(TState s) {
  return VecR3<double>{std::cos(k * s.position.z - omega * s.t),
                       std::sin(k * s.position.z - omega * s.t), 0} *
         E0 / sqrt2;
}

auto verlet_step(TState s, VecR3<double> acceleration) {
  TState next;
  next.t = s.t + dt;
  next.position =
      s.position + (s.velocity * dt) + (dt * dt * acceleration / 2.);
  const auto next_acceleration = force(next) / m;
  next.velocity = s.velocity + (acceleration + next_acceleration) * dt / 2.;
  return next;
}

void n_steps(unsigned n, TState state0) {
  print_tstate(state0);
  if (n == 0)
    return;
  else {
    auto state = state0;
    for (unsigned k = 0; k < n; ++k) {
      state = verlet_step(state, force(state) / m);
      print_tstate(state);
    }
  }
}

int main() {
  n_steps(steps_for_two_cycles, TState{0.,
                                       {-E0 / sqrt2 / omega / omega, 0, 0},
                                       {0, E0 / sqrt2 / omega, -0.25}});
  return 0;
}
