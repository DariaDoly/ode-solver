#include <Eigen/Dense>
#include <cmath>
#include <functional>
#include <iostream>
#include <iomanip>

#include "ode.h"

using State = Eigen::VectorXd;
using Rhs = std::function<State(double, const State&)>;

State time_integration(const std::function<State(const Rhs&, double, const State&, double)>& method, const Rhs& f, const State& y0, double t0, double t1, int n){
	double h = (t1 - t0)/n;
	double t = t0;
	State y = y0;
	for (std::size_t i = 0; i < n; ++i) {
		t += h;
		State y_new = method(f, t, y, h);
		y = y_new;
    }
	return y;
}

State RHS(double t, const State& y){
	State rhs_v = Eigen::VectorXd::Zero(y.size());
	rhs_v(0) = y(1);
	rhs_v(1) = -y(0);
	return rhs_v;
}

int main() {
	
	double t0 = 0.0;
	double t1 = 10.0;
	
	State y0 = Eigen::VectorXd::Zero(2);
	y0(0) = 1;
	
	std::cout << "n;    Euler_error; Euler_error_ratio; RK4_error; RK4_error_ratio; " << "\n";
	double exact = std::cos(t1);
	
	double err_eu_old = 0.0;
    double err_rk_old = 0.0;	
	
	for (std::size_t n = 100; n <= 3200; n *= 2) {
	    State y1 = time_integration(euler_step, RHS, y0, t0, t1, static_cast<int>(n));
		State y2 = time_integration(rk4_step, RHS, y0, t0, t1, static_cast<int>(n));
		double err_eu = std::abs(y1(0) - exact);
		double err_rk = std::abs(y2(0) - exact);
		std::cout << n << ";  ";
		if (n==100) {
		    std::cout << err_eu << ";               ; ";
			std::cout << err_rk << ";               ;";
		}
		else {
			std::cout << err_eu << "; " << err_eu_old/err_eu << "; ";
			std::cout << err_rk << "; " << err_rk_old/err_rk << "; ";
		}
		std::cout << "\n";
		err_eu_old = err_eu;
		err_rk_old = err_rk;
	}
	

    return 0;
}