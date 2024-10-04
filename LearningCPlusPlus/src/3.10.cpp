#include <cctype>
#include <iostream>
#include <string>

int main()
{
  std::string s1;
  std::cin >> s1;
  for (auto& c : s1)
  {
     if (std::ispunct(c))
    {
      c = ' ';
    }
  }
  std::cout << s1 << std::endl;

  return 0;
}