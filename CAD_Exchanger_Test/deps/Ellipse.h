#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "Curve3D.h"

class Ellipse : public Curve3D {
private:
  double radiusX;
  double radiusY;

public:
  Ellipse(double rx, double ry);

  std::vector<double> getPoint(double t) const override;
  std::vector<double> getDerivative(double t) const override;
};

#endif // ELLIPSE_H
