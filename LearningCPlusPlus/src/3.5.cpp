#include <iostream>
#include <string>

int main()
{
  std::string s1;
  std::string s2;
  std::string s3;

  for (;;)
  {
    std::cin >> s1 >> s2;
    s3 = s1 + s2;
    std::cout << s3 << " ";
  }
  return 0; }