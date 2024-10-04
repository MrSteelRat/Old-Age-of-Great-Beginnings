#include <iostream>

using std::cout;
using std::endl;

int main()
{
  size_t sum = 0;
  size_t val = 50;
  size_t max = 100;

  while (val <= max)
  {
    sum += val;
    ++val;
  }
  cout << "Sum of numbers from 50 to 100 is " << sum << endl;
  return 0; }