#ifndef CIRCLE_H
#define CIRCLE_H

#include "Curve3D.h"

class Circle : public Curve3D {
private:
  double radius;

public:
  Circle(double r);

  std::vector<double> getPoint(double t) const override;
  std::vector<double> getDerivative(double t) const override;
  double getRadius() const;
};

#endif // CIRCLE_H
