#include <Eigen/Dense>
#include <functional>

#include "ode.h"

using State = Eigen::VectorXd;
using Rhs = std::function<State(double, const State&)>;

State euler_step(const Rhs& f, double t, const State& y, double h){
	return y + h*f(t,y);
}

State rk4_step(const Rhs& f, double t, const State& y, double h){
	State k1 = f(t, y);
	State k2 = f(t + h/2, y + h/2*k1);
	State k3 = f(t + h/2, y + h/2*k2);
	State k4 = f(t + h, y + h*k3);
	return y + h/6*(k1 + 2*k2 + 2*k3 + k4);
}