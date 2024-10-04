#include <iostream>

using std::cout;
using std::endl;

int main()
{
  size_t val = 10;
  size_t zero = 0;
  while (val >= zero)
  {
    cout << val << endl;
    --val;
  }
  return 0;
}