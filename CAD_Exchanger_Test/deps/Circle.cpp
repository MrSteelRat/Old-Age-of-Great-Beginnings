#include "Circle.h"
#include <algorithm>
#include <cmath>

Circle::Circle(double r) : radius(std::max(r, 0.0)) {}

std::vector<double> Circle::getPoint(double t) const {
  return { radius * cos(t), radius * sin(t), 0.0 };
}

std::vector<double> Circle::getDerivative(double t) const {
  return { -radius * sin(t), radius * cos(t), 0.0 };
}

double Circle::getRadius() const {
  return radius;
}
