#include <iostream>
#include <vector>
#include <string>

int main()
{
  std::vector<std::string> v2;
  std::string s1;
  while (std::cin >> s1)
  {
    v2.push_back(s1);
    std::cout << s1 << std::endl;
  }
  return 0;
}