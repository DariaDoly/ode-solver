#pragma once
#include <Eigen/Dense>
#include <functional>
#include <vector>

#include "types.h"

using Method = std::function<State(const Rhs&, double, const State&, double)>;
using Observer = std::function<void(double, const State&)>;

State euler_step(const Rhs& f, double t, const State& y, double h);
State rk4_step(const Rhs& f, double t, const State& y, double h);

State time_integration(const Method& method, const Rhs& f, const State& y0, double t0, double t1, int n);

std::vector<State> trajectory(const Method& method, const Rhs& f,
                              const State& y0, double t0, double t1, int n);
							  
void integrate(const Method& method, const Rhs& f, State y,
               double t0, double t1, int n, const Observer& observe);