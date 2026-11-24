#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "io.h"

void write_csv(const std::string& filename, double t0, double h,
               const std::vector<State>& traj, const std::string& header){
    std::ofstream out(filename);
    if (!out) {
        std::cerr << "cannot open " << filename << "\n";
        return;
    }
	out << std::setprecision(10);
    out << header;
	out << "\n";
	for (std::size_t i = 0; i < traj.size(); ++i) {
        const State& s = traj[i];
        out << t0 + i * h;
        for (Eigen::Index j = 0; j < s.size(); ++j) {
            out << "," << s(j);
        }
        out << "\n";
    }
}