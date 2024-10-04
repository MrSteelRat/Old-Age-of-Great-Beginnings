#include <iostream>

int main(void)
{
  int sum = 0;
  for (int val = 50; val <= 100; val++)
  {
    sum += val;
  }
  std::cout << sum << std::endl;
  return 0;
}
