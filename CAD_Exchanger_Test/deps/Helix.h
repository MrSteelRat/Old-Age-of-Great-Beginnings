#ifndef HELIX_H
#define HELIX_H

#include "Curve3D.h"

constexpr auto M_PI = 3.14;

class Helix : public Curve3D {
private:
  double radius;
  double step;

public:
  Helix(double r, double s);

  std::vector<double> getPoint(double t) const override;
  std::vector<double> getDerivative(double t) const override;
};

#endif // HELIX_H
