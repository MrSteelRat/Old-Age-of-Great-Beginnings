#include <iostream>
#include <math.h>

int main(void)
{
  int x1;
  int x2;
  int y1;
  int y2;
  std::cin >> x1 >> y1;
  std::cin >> x2 >> y2;

  if (x1 == x2 || y1 == y2 || std::abs(x1 - x2) == std::abs(y1 - y2)) {
    std::cout << "YES\n";
  }
  else {
    std::cout << "NO\n";
  }
}
