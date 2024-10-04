#include <iostream>

int main()
{
  double inch = 2.54;
  double cm = 1.1;
  double answer;
  std::cin >> cm >> inch;
  answer = cm / inch;
  std::cout << answer;
  return 0;
}