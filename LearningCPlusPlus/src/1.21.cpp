#include <iostream>

#include "Sales_item.h"

int main()
{
  Sales_item item1;
  Sales_item item2;
  Sales_item result;

  std::cin >> item1 >> item2;
  if (item1.isbn() == item2.isbn())
  {
    std::cout << item1 + item2 << std::endl;
  }

  return 0;
}
