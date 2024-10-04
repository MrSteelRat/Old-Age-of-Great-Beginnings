#include <iostream>
#include <vector>

int main()
{
  std::vector<int> v2;
  int num;
  while (std::cin >> num)
  {
    v2.push_back(num);
    std::cout << num << std::endl; 
  }
  return 0;
}