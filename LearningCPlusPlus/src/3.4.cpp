#include <iostream>
#include <string>

int main()
{
  std::string s1;
  std::string s2;
  for (;;)
  {
    std::cin >> s1 >> s2;
    if (s1 == s2)
    {
      std::cout << "s1 = s2";
    }
    else if (s1 < s2)
    {
      std::cout << "s1 < s2";
    }
    else
    {
      std::cout << "s1 > s2";
    }
  }

  return 0; 
}