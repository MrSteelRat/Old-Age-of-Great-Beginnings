#include "Ellipse.h"
#include <algorithm>
#include <cmath>

Ellipse::Ellipse(double rx, double ry) : radiusX(std::max(rx, 0.0)), radiusY(std::max(ry, 0.0)) {}

std::vector<double> Ellipse::getPoint(double t) const {
  return { radiusX * cos(t), radiusY * sin(t), 0.0 };
}

std::vector<double> Ellipse::getDerivative(double t) const {
  return { -radiusX * sin(t), radiusY * cos(t), 0.0 };
}
