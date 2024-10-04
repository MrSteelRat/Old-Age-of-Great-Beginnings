#include <iostream>

int main()
{
  int a, b, c;
  std::cin >> a >> b >> c;

  if (a + b <= c || a + c <= b || b + c <= a)
  {
    std::cout << "UNDEFINED\n";
  }
  else if (a * a + b * b == c * c || a * a + c * c == b * b ||
           b * b + c * c == a * a)
  {
    std::cout << "YES\n";
  }
  else
  {
    std::cout << "NO\n";
  }
}
