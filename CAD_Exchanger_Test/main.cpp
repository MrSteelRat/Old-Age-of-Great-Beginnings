#include "deps/Circle.h"
#include "deps/Ellipse.h"
#include "deps/Helix.h"
#include <iostream>
#include <list>
#include <memory>
#include <omp.h>

int main() {
  // Create a container for curves
  std::vector<std::unique_ptr<Curve3D>> curves;
  curves.push_back(std::make_unique<Circle>(2.0));
  curves.push_back(std::make_unique<Ellipse>(3.0, 1.5));
  curves.push_back(std::make_unique<Helix>(1.0, 0.5));

  // Print coordinates of points and derivatives at t=PI/4
#pragma omp parallel for
  for (size_t i = 0; i < curves.size(); ++i) {
    std::vector<double> point = curves[i]->getPoint(M_PI / 4);
    std::vector<double> derivative = curves[i]->getDerivative(M_PI / 4);

#pragma omp critical
    {
      std::cout << "Curve " << i << ": ";
      std::cout << "Point: (" << point[0] << ", " << point[1] << ", " << point[2] << ") ";
      std::cout << "Derivative: (" << derivative[0] << ", " << derivative[1] << ", " << derivative[2] << ")\n";
    }
  }

  // Create a container to store pointers to Circle objects
  std::list<Circle*> circleContainer;

  // Filling a container using dynamic_cast and pointers
#pragma omp parallel for
  for (size_t i = 0; i < curves.size(); ++i) {
    auto* circle = dynamic_cast<Circle*>(curves[i].get());
    if (circle) {
#pragma omp critical
      {
        circleContainer.push_back(circle);
      }
    }
  }

  // Sort the container by radius
#pragma omp parallel
  {
#pragma omp single
    {
      circleContainer.sort([](const Circle* a, const Circle* b) {
        return a->getRadius() < b->getRadius();
        });
    }
  }

  // Calculate the total sum of radii
  double totalSum = 0.0;
#pragma omp parallel for reduction(+:totalSum)
  for (const auto& circle : circleContainer) {
    totalSum += circle->getRadius();
  }

  std::cout << "Total sum of radii: " << totalSum << std::endl;

  return 0;
}
