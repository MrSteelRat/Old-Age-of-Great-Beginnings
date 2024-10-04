#include <iostream>

int main(void)
{
  int numberOne;
  int numberTwo;
  std::cin >> numberOne >> numberTwo;
  if (numberOne <= numberTwo)
  {
    while (numberOne <= numberTwo)
    {
      std::cout << numberOne++;
    }
  }
  else
  {
    while (numberTwo <= numberOne)
    {
      std::cout << numberTwo++;
    }
  }
  return 0;
}
