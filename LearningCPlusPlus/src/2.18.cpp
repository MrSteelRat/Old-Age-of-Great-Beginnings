#include <iostream>

int main()
{
  int a = 2;
  int b = 3;

  int* p = &a;  // p1 points to a
  std::cout << "value a = " << a << std::endl;
  std::cout << "value b = " << b << std::endl;
  std::cout << "addr a " << &a << std::endl;
  std::cout << "addr b " << &b << std::endl;
  std::cout << p << std::endl;
  std::cout << *p << std::endl;
  p = &b;
  std::cout << p << '\n';
  *p = 10;
  std::cout << *p << std::endl;
}