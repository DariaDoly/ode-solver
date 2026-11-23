#include <Eigen/Dense>
#include <functional>

#include "ode.h"

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



State time_integration(const Method& method, const Rhs& f, const State& y0, double t0, double t1, int n){
	double h = (t1 - t0)/n;
	double t = t0;
	State y = y0;
	for (int i = 0; i < n; ++i) {
		y = method(f, t, y, h);
		t += h;
    }
	return y;
}