#include <iostream>
#include <string>
#include <cctype>

int main()
{
  std::string s1 = ("AAA aaa AaA aAa");
  
  for (auto &c : s1)
  {
    if (std::isupper(c))
    {
      c = 'X';
    }
    else if (std::islower(c))
    {
      c = 'x';
    }
  }
  std::cout << s1 << std::endl;

  return 0;
}