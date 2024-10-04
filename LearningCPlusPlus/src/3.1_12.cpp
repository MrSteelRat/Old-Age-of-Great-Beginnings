#include <iostream>

using std::cout;
using std::cin;

int main(void)
{ 
  int numberOne;
  int numberTwo;
  cin >> numberOne >> numberTwo;
  if (numberOne <= numberTwo)
  {
    while (numberOne <= numberTwo)
    {
      cout << numberOne++;
    }
  }
  else
  {
    while (numberTwo <= numberOne)
    {
     cout << numberTwo++;
    }
  }
  return 0;
}
