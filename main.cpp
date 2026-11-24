#include <numbers>
#include <Eigen/Dense>
#include <cmath>
#include <functional>
#include <iostream>
#include <iomanip>

#include "ode.h"
#include "io.h"

State oscillator(double, const State& y){
	State rhs_v = Eigen::VectorXd::Zero(y.size());
	rhs_v(0) = y(1);
	rhs_v(1) = -y(0);
	return rhs_v;
}

State rhs_cos(double t, const State&){
	State rhs_v = Eigen::VectorXd::Zero(1);
	rhs_v(0) = std::cos(t);
	return rhs_v;
}

State kepler(double, const State& y){
	State rhs_v = Eigen::VectorXd::Zero(y.size());
	double abs_r = std::sqrt(y(0)*y(0)+y(1)*y(1));
	rhs_v(0) = y(2);
	rhs_v(1) = y(3);
	rhs_v(2) = -y(0)/abs_r/abs_r/abs_r;
	rhs_v(3) = -y(1)/abs_r/abs_r/abs_r;
	return rhs_v;
}

void convergence_table(const Rhs& f, const State& y0,
                       double t0, double t1, double exact){
	std::cout << "n;    Euler_error; Euler_error_ratio; RK4_error; RK4_error_ratio; " << "\n";

	double err_eu_old = 0.0;
    double err_rk_old = 0.0;	
	
    for (int n = 100; n <= 3200; n *= 2) {
		State y1 = time_integration(euler_step, f, y0, t0, t1, n);
		State y2 = time_integration(rk4_step, f, y0, t0, t1, n);
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
	
}

int main() {
	
/* 	double t0 = 0.0;
	double t1 = 10.0;
	
	State y0_osc = Eigen::VectorXd::Zero(2);
	y0_osc(0) = 1;
	double exact_osc = std::cos(t1);
	std::cout << "Oscillator:   \n";
	convergence_table(oscillator, y0_osc, t0, t1, exact_osc);
	
	State y0_cos = Eigen::VectorXd::Zero(1);
	double exact_sin = std::sin(t1);
	std::cout << "Sine:   \n";
	convergence_table(rhs_cos, y0_cos, t0, t1, exact_sin); */
	
	double t0 = 0.0;
	double t1 = 20.0*std::numbers::pi;
	int n = 2000;
	
	State y0_kep = Eigen::VectorXd::Zero(4);
	y0_kep(0) = 1;
	y0_kep(3) = 1;
	
	std::string filename_euler = "orbit_euler.csv";
	std::string filename_rk4 = "orbit_rk4.csv";
	std::string header = "t,x,y,vx,vy";
	
	std::vector<State> traj_euler = trajectory(euler_step, kepler, y0_kep, t0, t1, n);
	std::vector<State> traj_rk4 = trajectory(rk4_step, kepler, y0_kep, t0, t1, n);
	
	double h = (t1 - t0)/n;
	
	write_csv(filename_euler, t0, h, traj_euler, header);
	write_csv(filename_rk4, t0, h, traj_rk4, header);

    return 0;
}