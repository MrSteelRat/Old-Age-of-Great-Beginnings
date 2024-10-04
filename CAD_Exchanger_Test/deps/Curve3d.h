#ifndef CURVE3D_H
#define CURVE3D_H

#include <vector>

class Curve3D {
public:
  virtual ~Curve3D() {}

  virtual std::vector<double> getPoint(double t) const = 0;
  virtual std::vector<double> getDerivative(double t) const = 0;
};

#endif // CURVE3D_H
