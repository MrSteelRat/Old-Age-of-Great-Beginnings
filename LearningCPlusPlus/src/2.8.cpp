#include <iostream>

int main()
{
  // 2M followed by a newline
  std::cout << "\062\115" << std::endl;  // "2M" octal decimals
  // 2, then a tab, then an M, followed by a newline
  // any of followings would work:
  std::cout << "\062\t\115\n";      // octal decimals and escape characters
  std::cout << "\062\011\115\012";  // octal decimals
  std::cout << "\x32\x09\x4d\x0a";  // hexadecimals
  return 0;
}
