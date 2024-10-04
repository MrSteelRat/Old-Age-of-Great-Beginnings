#include <iostream>

int numberOne;
int numberTwo;

int main(void)
{
  std::cin >> numberOne >> numberTwo;
  if (numberOne <= numberTwo)
  {
    for (; numberOne <= numberTwo; numberOne++)
    {
      std::cout << numberOne;
    }
  }
  else
  {
    for (; numberTwo <= numberOne; numberTwo++)
    {
      std::cout << numberTwo;
    }
  }
  return 0;
}
