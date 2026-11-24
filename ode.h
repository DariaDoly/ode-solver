#pragma once
#include <Eigen/Dense>
#include <functional>
#include <vector>

using State = Eigen::VectorXd;
using Rhs = std::function<State(double, const State&)>;
using Method = std::function<State(const Rhs&, double, const State&, double)>;

State euler_step(const Rhs& f, double t, const State& y, double h);
State rk4_step(const Rhs& f, double t, const State& y, double h);

State time_integration(const Method& method, const Rhs& f, const State& y0, double t0, double t1, int n);

std::vector<State> trajectory(const Method& method, const Rhs& f,
                              const State& y0, double t0, double t1, int n);