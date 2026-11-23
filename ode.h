#pragma once
#include <Eigen/Dense>
#include <functional>

using State = Eigen::VectorXd;
using Rhs = std::function<State(double, const State&)>;

State euler_step(const Rhs& f, double t, const State& y, double h);
State rk4_step(const Rhs& f, double t, const State& y, double h);