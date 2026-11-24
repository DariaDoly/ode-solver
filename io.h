#pragma once
#include <vector>
#include <string>

#include "ode.h"

void write_csv(const std::string& filename, double t0, double h,
               const std::vector<State>& traj, const std::string& header);