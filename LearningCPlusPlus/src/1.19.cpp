#include <iostream>

int main()
{
  int numberOne = 0;
  int numberTwo = 0;

  std::cin >> numberOne >> numberTwo;

  if (numberOne > numberTwo)
  {
    int temp = numberOne;
    numberOne = numberTwo;
    numberTwo = temp;
  }
  
  while (numberOne <= numberTwo)
  {
    std::cout << numberOne << std::endl;
    ++numberOne;
  }

  return 0;
}
