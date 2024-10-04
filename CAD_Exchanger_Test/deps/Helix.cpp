#include "Helix.h"
#include <algorithm>
#include <cmath>

Helix::Helix(double r, double s) : radius(std::max(r, 0.0)), step(s) {}

std::vector<double> Helix::getPoint(double t) const {
  return { radius * cos(t), radius * sin(t), step * t / (2 * M_PI) };
}

std::vector<double> Helix::getDerivative(double t) const {
  return { -radius * sin(t), radius * cos(t), step / (2 * M_PI) };
}
