#include <iostream>

#include "Sales_item.h"

int main()
{
  Sales_item item1;
  Sales_item item2;

  int count = 0;
  std::cout << "Enter items: " << std::endl;
  if (std::cin >> item1)
  {
    std::cerr << "Not valid data";
  }
  ++count;

  while (std::cin >> item2)
  {
    if (item2.isbn() != item1.isbn())
    {
      std::cerr << "ISBN mis search" << std::endl;
    }
    ++count;
  }

  std::cout << count << std::endl;
  return 0;
}
