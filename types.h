#pragma once
#include <Eigen/Dense>
#include <functional>

using State = Eigen::VectorXd;
using Rhs = std::function<State(double, const State&)>;